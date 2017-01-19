#include "CActionNotifySMSSendFailure.h"
#include <ATProtocolEngine/IActionExecutionContext.h>
#include "IGSMActionContext.h"
#include "GSMDaemon/ISMSServiceListener.h"

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
		m_rGSMActionContext.GetSMSServiceListener()->NotifySMSSendFailure();
	}
}

}
