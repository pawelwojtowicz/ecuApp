#pragma once
#include <ATProtocolEngine/IATProtocolActionFactory.h>

namespace ATProtocolEngine
{
class IActionExecutionContext;
}

namespace GSMModemSim800L
{
class IGSMActionContext;
class CGSMModemActionFactory : public ATProtocolEngine::IATProtocolActionFactory
{
public:
	CGSMModemActionFactory(IGSMActionContext& actionContext, ATProtocolEngine::IActionExecutionContext& rContext);
	virtual ~CGSMModemActionFactory();

private:
	virtual ATProtocolEngine::CATProtocolAction* CreateActionInstance( const std::string& actionName ) const;	

private:
	IGSMActionContext& m_rGSMModemActionContext;

	ATProtocolEngine::IActionExecutionContext& m_rATProtocolEngineContext;
};
}
