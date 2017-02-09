#include "CActionDetermineNextStep.h"
#include <ATProtocolEngine/IActionExecutionContext.h>
#include "IGSMActionContext.h"
#include "CSMSOutbox.h"
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
	else if ( m_rGSMActionContext.GetSMSOutbox().QueueNotEmpty() )
	{
		CSMSOutbox::tSMS sms;
		if ( m_rGSMActionContext.GetSMSOutbox().GetNextMessage( sms ) )
		{
			GetExecutionContext().GetParameterBundle().Store( sc_CMGS_trgtNumber, sms.TrgtNumber);
			GetExecutionContext().GetParameterBundle().Store( sc_CMGS_msgText, sms.MessageText+std::string("\x1A"));

			char orderIDTxt[25];
			sprintf(orderIDTxt, "%d", sms.MessageId);
			GetExecutionContext().GetParameterBundle().Store(sc_CMGS_orderID, orderIDTxt);


			GetExecutionContext().DispatchEvent("E_SEND_SMS");
		}
	}
}

}
