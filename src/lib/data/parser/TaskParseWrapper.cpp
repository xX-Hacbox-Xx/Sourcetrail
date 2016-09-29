#include "data/parser/TaskParseWrapper.h"

#include "component/view/DialogView.h"
#include "utility/file/FileRegister.h"
#include "utility/scheduling/Blackboard.h"
#include "utility/utility.h"

TaskParseWrapper::TaskParseWrapper(
	std::shared_ptr<FileRegister> fileRegister,
	DialogView* dialogView
)
	: m_fileRegister(fileRegister)
	, m_dialogView(dialogView)
{
}

TaskParseWrapper::~TaskParseWrapper()
{
}

void TaskParseWrapper::setTask(std::shared_ptr<Task> task)
{
	if (task)
	{
		m_taskRunner = std::make_shared<TaskRunner>(task);
	}
}

void TaskParseWrapper::doEnter(std::shared_ptr<Blackboard> blackboard)
{
	blackboard->set("indexer_count", 0);
	m_dialogView->updateIndexingDialog(0, m_fileRegister->getSourceFilesCount(), "");

	m_start = utility::durationStart();
}

Task::TaskState TaskParseWrapper::doUpdate(std::shared_ptr<Blackboard> blackboard)
{
	return m_taskRunner->update(blackboard);
}

void TaskParseWrapper::doExit(std::shared_ptr<Blackboard> blackboard)
{
	blackboard->clear("indexer_count");
	blackboard->set("index_time", utility::duration(m_start));
}

void TaskParseWrapper::doReset(std::shared_ptr<Blackboard> blackboard)
{
	m_taskRunner->reset();
}
