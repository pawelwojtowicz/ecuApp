#include "CActionNotifySMSSendFailure.h"
#include <ATProtocolEngine/IActionExecutionContext.h>
#include "IGSMActionContext.h"
#include "GSMDaemon/ISMSServiceListener.h"
#include "GSMModemSim800L/GSMModemSim800LConst.h"

namespace GSMModemSim800L
{

CActionNotifySMSSendFailure::CActionNotifySMSSendFailure(IGSMActionContext& rGSMActionContext, ATProtocolEngine::IActionExecutionContext& rATPrtEngineContext)
: ATProtocolEngine::CATProtocolAction(rATPrtEngineContext)
, m_rGSMActionContext(rGSMActionContext)
{
}

CActionNotifySMSSendFailure::~CActionNotifySMSSendFailure()
{
}

void CActionNotifySMSSendFailure::Execute()
{
	if ( 0 != m_rGSMActionContext.GetSMSServiceListener() )
	{
		std::string idString(GetExecutionContext().GetParameterBundle().GetParameter(sc_CMGS_orderID));
		UInt32 messageId( atoi(idString.c_str()));

		m_rGSMActionContext.GetSMSServiceListener()->NotifySMSSendFailure(messageId);


		GetExecutionContext().DispatchEvent("E_SENDING_DONE");
	}
}

}
