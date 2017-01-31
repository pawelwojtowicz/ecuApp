#pragma once
#include <ATProtocolEngine/CATProtocolAction.h>

namespace ATProtocolEngine
{
class IActionExecutionContext;
}

namespace GSMModemSim800L
{
class IGSMActionContext;

class CActionNotifyVoiceServiceEvents : public ATProtocolEngine::CATProtocolAction
{
public:
	typedef enum
	{
		vcNumberBusy,
		vcConnectionEstablished,
		vcConnectionTerminated,
		vcIncommingCall,
		vcIncommingCallWithNumber,
		vcDTMFCode
	} tVoiceEventType;
	CActionNotifyVoiceServiceEvents( const tVoiceEventType type, IGSMActionContext& rGSMActionContext, ATProtocolEngine::IActionExecutionContext& rATPrtEngineContext);
	virtual ~CActionNotifyVoiceServiceEvents();

	//virtual bool Configure( const CSM::IActionFactory& , const std::string& configurationString );

	virtual void Execute();

private:
	CActionNotifyVoiceServiceEvents(const CActionNotifyVoiceServiceEvents&);
	CActionNotifyVoiceServiceEvents& operator=( const CActionNotifyVoiceServiceEvents&);

private:
	IGSMActionContext& m_rGSMActionContext;

	tVoiceEventType m_voiceEventType;
};
}
