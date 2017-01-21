#include "CGSMModemActionFactory.h"
#include <ATProtocolEngine/CATProtocolAction.h>
#include <ATProtocolEngine/IActionExecutionContext.h>
#include "IGSMActionContext.h"
#include "CActionNotifySMSSent.h"
#include "CActionNotifySMSSendFailure.h"
#include "CActionNotifyIncomingSMS.h"
#include "CActionNotifyModemInfo.h"
#include "CActionNotifyRegistrationState.h"
#include "CActionNotifySignalStrength.h"

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

	if ( !actionName.compare("NotifySMSSent") )
	{
		pAction = new CActionNotifySMSSent(m_rGSMModemActionContext, m_rATProtocolEngineContext);
	}
	else if (!actionName.compare("NotifySMSSendFailure"))
	{
		pAction = new CActionNotifySMSSendFailure(m_rGSMModemActionContext, m_rATProtocolEngineContext);
	}
	else if (!actionName.compare("NotifyIncomingSMS"))
	{
		pAction = new CActionNotifyIncomingSMS(m_rGSMModemActionContext, m_rATProtocolEngineContext);
	}
	else if ( !actionName.compare( "NotifyModemManufacturerReceived" ))
	{
		pAction = new CActionNotifyModemInfo(CActionNotifyModemInfo::mdmManufacturer ,m_rGSMModemActionContext, m_rATProtocolEngineContext);
	}
	else if ( !actionName.compare( "NotifyModemTypeReceived" ))
	{
		pAction = new CActionNotifyModemInfo(CActionNotifyModemInfo::mdmTypeSeries ,m_rGSMModemActionContext, m_rATProtocolEngineContext);
	}
	else if ( !actionName.compare( "NotifyModemIMEIReceived" ))
	{
		pAction = new CActionNotifyModemInfo(CActionNotifyModemInfo::mdmIMEI ,m_rGSMModemActionContext, m_rATProtocolEngineContext);
	}
	else if (!actionName.compare("NotifyRegStateReceived"))
	{
		pAction = new CActionNotifyRegistrationState(m_rGSMModemActionContext, m_rATProtocolEngineContext);
	}
	else if (!actionName.compare("NotifySignalStrengthReceived") )
	{
		pAction = new CActionNotifySignalStrength(m_rGSMModemActionContext, m_rATProtocolEngineContext);
	}

	return pAction;
}

}
