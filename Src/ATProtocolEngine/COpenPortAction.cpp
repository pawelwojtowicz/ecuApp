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
	if ( GetExecutionContext().GetSerialPortHandler().OpenPort() )
	{
		GetExecutionContext().DispatchEvent("E_PORT_OK");
	}
}
}
