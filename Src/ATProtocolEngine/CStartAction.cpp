#include "CStartAction.h"

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
	GetExecutionContext().GetSerialPortHandler().StartProcessing();
}
}
