#include "CActionNotifyVoiceServiceEvents.h"
#include <ATProtocolEngine/IActionExecutionContext.h>
#include "IGSMActionContext.h"
#include "GSMModemSim800LConst.h"
#include "GSMDaemon/IVoiceServiceListener.h"

namespace GSMModemSim800L
{

CActionNotifyVoiceServiceEvents::CActionNotifyVoiceServiceEvents(const tVoiceEventType eventType,IGSMActionContext& rGSMActionContext, ATProtocolEngine::IActionExecutionContext& rATPrtEngineContext)
: ATProtocolEngine::CATProtocolAction(rATPrtEngineContext)
, m_rGSMActionContext(rGSMActionContext)
, m_voiceEventType(eventType)
{

}

CActionNotifyVoiceServiceEvents::~CActionNotifyVoiceServiceEvents()
{
}

void CActionNotifyVoiceServiceEvents::Execute()
{
	if ( 0 != m_rGSMActionContext.GetVoiceServiceListener() )
	{
		switch(m_voiceEventType)
		{
		case vcNumberBusy:
		{
			m_rGSMActionContext.GetVoiceServiceListener()->NotifyBusy( );
		};break;
		case vcConnectionEstablished:
		{
			m_rGSMActionContext.GetVoiceServiceListener()->NotifyConnectionEstablished();
		};break;
		case vcConnectionTerminated:
		{
			m_rGSMActionContext.GetVoiceServiceListener()->NotifyConnectionTerminated();
		};break;
		case vcIncommingCall:
		{
			m_rGSMActionContext.GetVoiceServiceListener()->NotifyIncomingCall();
		};break;
		case vcIncommingCallWithNumber:
		{
			if (GetExecutionContext().GetParameterBundle().IsAvailable(sc_CLIP_number) )
			{
				m_rGSMActionContext.GetVoiceServiceListener()->NotifyIncomingCallNumber(GetExecutionContext().GetParameterBundle().GetParameter(sc_CLIP_number) );
			}
		};break;
		case vcDTMFCode:
		{
			if (GetExecutionContext().GetParameterBundle().IsAvailable(sc_DTMF_code) )
			{
				m_rGSMActionContext.GetVoiceServiceListener()->NotifyDTMFCode(GetExecutionContext().GetParameterBundle().GetParameter(sc_DTMF_code) );
			}

		};break;
		default:;
		};
	}
}

}
