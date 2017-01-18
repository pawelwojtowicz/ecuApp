#pragma once
#include <ATProtocolEngine/IATProtocolActionFactory.h>

namespace GSMModemSim800L
{
class IGSMActionContext;
class CGSMModemActionFactory : public ATProtocolEngine::IATProtocolActionFactory
{
public:
	CGSMModemActionFactory(IGSMActionContext& actionContext);
	virtual ~CGSMModemActionFactory();

private:
	virtual ATProtocolEngine::CATProtocolAction* CreateActionInstance( const std::string& actionName ) const;	

private:
	IGSMActionContext& m_rActionContext;
};
}
