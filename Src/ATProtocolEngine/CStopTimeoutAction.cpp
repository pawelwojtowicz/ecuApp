#include "CStopTimeoutAction.h"
#include <stdlib.h>

namespace ATProtocolEngine
{

CStopTimeoutAction::CStopTimeoutAction(IActionExecutionContext& actionExecutionContext)
: CATProtocolAction(actionExecutionContext)
{
}

CStopTimeoutAction::~CStopTimeoutAction()
{
}

bool CStopTimeoutAction::Configure(const CSM::IActionFactory& , const std::string& )
{
	return true;
}

void CStopTimeoutAction::Execute()
{
	GetExecutionContext().GetTimeoutHandler().StopTimeout();
}
}
