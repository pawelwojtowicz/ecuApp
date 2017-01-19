#include "CActionNotifySMSSent.h"
#include <ATProtocolEngine/IActionExecutionContext.h>
#include "IGSMActionContext.h"
#include "GSMDaemon/ISMSServiceListener.h"

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
		m_rGSMActionContext.GetSMSServiceListener()->NotifySMSSendSuccess();
	}
}

}
