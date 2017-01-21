#include "CActionNotifyRegistrationState.h"
#include <ATProtocolEngine/IActionExecutionContext.h>
#include "IGSMActionContext.h"
#include "GSMModemSim800LConst.h"
#include "GSMDaemon/IModemListener.h"
namespace GSMModemSim800L
{

CActionNotifyRegistrationState::CActionNotifyRegistrationState(IGSMActionContext& rGSMActionContext, ATProtocolEngine::IActionExecutionContext& rATPrtEngineContext)
: ATProtocolEngine::CATProtocolAction(rATPrtEngineContext)
, m_rGSMActionContext(rGSMActionContext)
{

}

CActionNotifyRegistrationState::~CActionNotifyRegistrationState()
{
}

void CActionNotifyRegistrationState::Execute()
{
	if ( 0 != m_rGSMActionContext.GetModemListener() )
	{
		if ( GetExecutionContext().GetParameterBundle().IsAvailable(sc_CREG_regStatus) )
		{
			std::string info(GetExecutionContext().GetParameterBundle().GetParameter(sc_CREG_regStatus));

			GSMDaemon::tNetworkRegistrationState regState(static_cast<GSMDaemon::tNetworkRegistrationState>(atoi(info.c_str())));

			m_rGSMActionContext.GetModemListener()->NotifyRegistrationStateReceived( regState );
		}
	}
}

}
