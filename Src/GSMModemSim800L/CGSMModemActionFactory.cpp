#include "CGSMModemActionFactory.h"
#include <ATProtocolEngine/CATProtocolAction.h>
#include <ATProtocolEngine/IActionExecutionContext.h>
#include "IGSMActionContext.h"

namespace GSMModemSim800L
{

CGSMModemActionFactory::CGSMModemActionFactory(IGSMActionContext& rGSMActionContext, ATProtocolEngine::IActionExecutionContext& rATPrtEngineContext)
: m_rGSMModemActionContext(rGSMActionContext)
, m_rATProtocolEngineContext(rATPrtEngineContext)
{
}

CGSMModemActionFactory::~CGSMModemActionFactory()
{
}

ATProtocolEngine::CATProtocolAction* CGSMModemActionFactory::CreateActionInstance( const std::string& actionName ) const
{
	ATProtocolEngine::CATProtocolAction* pAction(0);

	return pAction;
}

}
