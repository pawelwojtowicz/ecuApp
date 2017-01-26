#include "CStartAction.h"
#include <Logger/Logger.h>

namespace ATProtocolEngine
{
CStartAction::CStartAction(IActionExecutionContext& actionExecutionContext)
: CATProtocolAction(actionExecutionContext)
{
}

CStartAction::~CStartAction()
{
}

void CStartAction::Execute()
{
	RETAILMSG(INFO, ("CStartAction::Execute()"));
	GetExecutionContext().GetSerialPortHandler().StartProcessing();
}
}
