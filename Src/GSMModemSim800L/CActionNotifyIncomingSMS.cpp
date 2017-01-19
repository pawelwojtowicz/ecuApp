#include "CActionNotifyIncomingSMS.h"
#include <ATProtocolEngine/IActionExecutionContext.h>
#include "IGSMActionContext.h"
#include "GSMDaemon/ISMSServiceListener.h"

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
		if ( 	GetExecutionContext().GetParameterBundle().IsAvailable("PHONE_NUMBER") && 
					GetExecutionContext().GetParameterBundle().IsAvailable("MSG_TIMESTAMP") &&
					GetExecutionContext().GetParameterBundle().IsAvailable("MSG_TEXT") )
		{
			m_rGSMActionContext.GetSMSServiceListener()->NotifyIncomingSMS(	GetExecutionContext().GetParameterBundle().GetParameter("PHONE_NUMBER"),
																																			GetExecutionContext().GetParameterBundle().GetParameter("MSG_TIMESTAMP"),
																																			GetExecutionContext().GetParameterBundle().GetParameter("MSG_TEXT") );
		}
	}
}

}
