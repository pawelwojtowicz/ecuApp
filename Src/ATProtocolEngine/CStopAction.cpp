#include "CStopAction.h"

namespace ATProtocolEngine
{
CStopAction::CStopAction(IActionExecutionContext& actionExecutionContext)
: CATProtocolAction(actionExecutionContext)
{
}

CStopAction::~CStopAction()
{
}

void CStopAction::Execute()
{
	GetExecutionContext().GetSerialPortHandler().StopProcessing();
}
}
