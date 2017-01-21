#include "CActionNotifyProviderName.h"
#include <ATProtocolEngine/IActionExecutionContext.h>
#include "IGSMActionContext.h"
#include "GSMModemSim800LConst.h"
#include "GSMDaemon/IModemListener.h"
namespace GSMModemSim800L
{

CActionNotifyProviderName::CActionNotifyProviderName(IGSMActionContext& rGSMActionContext, ATProtocolEngine::IActionExecutionContext& rATPrtEngineContext)
: ATProtocolEngine::CATProtocolAction(rATPrtEngineContext)
, m_rGSMActionContext(rGSMActionContext)
{

}

CActionNotifyProviderName::~CActionNotifyProviderName()
{
}

void CActionNotifyProviderName::Execute()
{
	if ( 0 != m_rGSMActionContext.GetModemListener() )
	{
		if ( GetExecutionContext().GetParameterBundle().IsAvailable(sc_COPS_operatorName) )
		{
			std::string providerName(GetExecutionContext().GetParameterBundle().GetParameter(sc_COPS_operatorName));

			m_rGSMActionContext.GetModemListener()->NotifyGSMProviderNameReceived( providerName );
		}
	}
}

}
