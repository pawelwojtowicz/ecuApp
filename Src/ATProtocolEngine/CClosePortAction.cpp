#include "CClosePortAction.h"

namespace ATProtocolEngine
{
CClosePortAction::CClosePortAction(IActionExecutionContext& actionExecutionContext)
: CATProtocolAction(actionExecutionContext)
{
}

CClosePortAction::~CClosePortAction()
{
}

void CClosePortAction::Execute()
{
	GetExecutionContext().GetSerialPortHandler().ClosePort();
}
}
