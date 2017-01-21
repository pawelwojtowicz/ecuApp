#pragma once
#include <ATProtocolEngine/CATProtocolAction.h>

namespace ATProtocolEngine
{
class IActionExecutionContext;
}

namespace GSMModemSim800L
{
class IGSMActionContext;

class CActionNotifyRegistrationState : public ATProtocolEngine::CATProtocolAction
{
public:
	CActionNotifyRegistrationState( IGSMActionContext& rGSMActionContext, ATProtocolEngine::IActionExecutionContext& rATPrtEngineContext);
	virtual ~CActionNotifyRegistrationState();

	//virtual bool Configure( const CSM::IActionFactory& , const std::string& configurationString );

	virtual void Execute();

private:
	CActionNotifyRegistrationState(const CActionNotifyRegistrationState&);
	CActionNotifyRegistrationState& operator=( const CActionNotifyRegistrationState&);

private:
	IGSMActionContext& m_rGSMActionContext;
};
}
