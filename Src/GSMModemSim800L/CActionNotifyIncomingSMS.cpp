#include "CActionNotifyIncomingSMS.h"
#include <ATProtocolEngine/IActionExecutionContext.h>
#include "IGSMActionContext.h"
#include "GSMDaemon/ISMSServiceListener.h"
#include "GSMModemSim800LConst.h"

namespace GSMModemSim800L
{

CActionNotifyIncomingSMS::CActionNotifyIncomingSMS(IGSMActionContext& rGSMActionContext, ATProtocolEngine::IActionExecutionContext& rATPrtEngineContext)
: ATProtocolEngine::CATProtocolAction(rATPrtEngineContext)
, m_rGSMActionContext(rGSMActionContext)
{
}

CActionNotifyIncomingSMS::~CActionNotifyIncomingSMS()
{
}

void CActionNotifyIncomingSMS::Execute()
{
	if ( 0 != m_rGSMActionContext.GetSMSServiceListener() )
	{
		if ( 	GetExecutionContext().GetParameterBundle().IsAvailable(sc_CMGL_msgOrgNo) && 
					GetExecutionContext().GetParameterBundle().IsAvailable(sc_CMGL_msgTimeStamp) &&
					GetExecutionContext().GetParameterBundle().IsAvailable(sc_CMGL_msgContent) )
		{
			m_rGSMActionContext.GetSMSServiceListener()->NotifyIncomingSMS(	GetExecutionContext().GetParameterBundle().GetParameter(sc_CMGL_msgOrgNo),
																																			GetExecutionContext().GetParameterBundle().GetParameter(sc_CMGL_msgTimeStamp),
																																			GetExecutionContext().GetParameterBundle().GetParameter(sc_CMGL_msgContent) );
		}
	}
}

}
