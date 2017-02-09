#include "CActionNotifySMSSent.h"
#include <ATProtocolEngine/IActionExecutionContext.h>
#include "IGSMActionContext.h"
#include "GSMDaemon/ISMSServiceListener.h"
#include "CSMSOutbox.h"
#include "GSMModemSim800L/GSMModemSim800LConst.h"


namespace GSMModemSim800L
{

CActionNotifySMSSent::CActionNotifySMSSent(IGSMActionContext& rGSMActionContext, ATProtocolEngine::IActionExecutionContext& rATPrtEngineContext)
: ATProtocolEngine::CATProtocolAction(rATPrtEngineContext)
, m_rGSMActionContext(rGSMActionContext)
{
}

CActionNotifySMSSent::~CActionNotifySMSSent()
{
}

void CActionNotifySMSSent::Execute()
{
	if ( 0 != m_rGSMActionContext.GetSMSServiceListener() )
	{
		std::string idString(GetExecutionContext().GetParameterBundle().GetParameter(sc_CMGS_orderID));
		UInt32 messageId( atoi(idString.c_str()));
		m_rGSMActionContext.GetSMSOutbox().ConfirmMsgSent( messageId );
		m_rGSMActionContext.GetSMSServiceListener()->NotifySMSSendSuccess(messageId);

		

		GetExecutionContext().DispatchEvent("E_SENDING_DONE");
	}
}

}
