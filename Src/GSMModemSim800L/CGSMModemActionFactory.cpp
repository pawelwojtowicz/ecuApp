#include "CGSMModemActionFactory.h"
#include <ATProtocolEngine/CATProtocolAction.h>
#include "IGSMActionContext.h"

namespace GSMModemSim800L
{

CGSMModemActionFactory::CGSMModemActionFactory(IGSMActionContext& rActionContext)
: m_rActionContext(rActionContext)
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
