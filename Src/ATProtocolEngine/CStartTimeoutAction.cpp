#include "CStartTimeoutAction.h"
#include <stdlib.h>

namespace ATProtocolEngine
{

CStartTimeoutAction::CStartTimeoutAction(IActionExecutionContext& actionExecutionContext)
: CATProtocolAction(actionExecutionContext)
, m_timeoutValue(0)
{
}

CStartTimeoutAction::~CStartTimeoutAction()
{
}

bool CStartTimeoutAction::Configure(const CSM::IActionFactory& , const std::string& configurationString)
{
	m_timeoutValue = atoi(configurationString.c_str());

	return ( 0 != m_timeoutValue );
}

void CStartTimeoutAction::Execute()
{
	GetExecutionContext().GetTimeoutHandler().StartTimeout(m_timeoutValue);
}
}
