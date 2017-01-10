#include "COpenPortAction.h"

namespace ATProtocolEngine
{
COpenPortAction::COpenPortAction(IActionExecutionContext& actionExecutionContext)
: CATProtocolAction(actionExecutionContext)
{
}

COpenPortAction::~COpenPortAction()
{
}

void COpenPortAction::Execute()
{
	GetExecutionContext().GetSerialPortHandler().OpenPort();
}
}
