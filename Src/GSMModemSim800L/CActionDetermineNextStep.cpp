#include "CActionDetermineNextStep.h"
#include <ATProtocolEngine/IActionExecutionContext.h>
#include "IGSMActionContext.h"
#include "GSMModemSim800LConst.h"
#include "GSMDaemon/IModemListener.h"
namespace GSMModemSim800L
{

CActionDetermineNextStep::CActionDetermineNextStep(IGSMActionContext& rGSMActionContext, ATProtocolEngine::IActionExecutionContext& rATPrtEngineContext)
: ATProtocolEngine::CATProtocolAction(rATPrtEngineContext)
, m_rGSMActionContext(rGSMActionContext)
{

}

CActionDetermineNextStep::~CActionDetermineNextStep()
{
}

void CActionDetermineNextStep::Execute()
{
	if ( GetExecutionContext().GetParameterBundle().IsAvailable(sc_ATD_trgtNumber) )
	{
	}
	else if ( GetExecutionContext().GetParameterBundle().IsAvailable(sc_CMTI_Received) )
	{
		printf("Incoming SMS was here\n");
		// get the SMSes
		GetExecutionContext().DispatchEvent("E_FETCH_INCOMING_SMS");
	}
/**	else if ( 1)
	{
		// send the SMS, in case the outbox is not empty
	}*/
}

}
