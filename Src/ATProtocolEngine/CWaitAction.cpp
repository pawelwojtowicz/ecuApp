#include "CWaitAction.h"
#include <unistd.h>

namespace ATProtocolEngine
{

	CWaitAction::CWaitAction(IActionExecutionContext& actionExecutionContext)
	: CATProtocolAction(actionExecutionContext)
	, m_microseconds(0)
	{
	}
	CWaitAction::~CWaitAction()
	{
	}

	bool CWaitAction::Configure(const CSM::IActionFactory& , const std::string& configurationString)
	{
		if ( !configurationString.empty())
		{
			m_microseconds = atoi(configurationString.c_str()) * 1000;
			return ( 0 != m_microseconds );
		}
		return false;
	}

	void CWaitAction::Execute()
	{
		if ( 0 != m_microseconds )
		{
			usleep(m_microseconds);
		}
	}
}
