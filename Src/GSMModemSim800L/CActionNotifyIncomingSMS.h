#pragma once
#include <ATProtocolEngine/CATProtocolAction.h>

namespace ATProtocolEngine
{
class IActionExecutionContext;
}

namespace GSMModemSim800L
{
class IGSMActionContext;

class CActionNotifyIncomingSMS : public ATProtocolEngine::CATProtocolAction
{
public:
	CActionNotifyIncomingSMS(IGSMActionContext& rGSMActionContext, ATProtocolEngine::IActionExecutionContext& rATPrtEngineContext);
	virtual ~CActionNotifyIncomingSMS();

	//virtual bool Configure( const CSM::IActionFactory& , const std::string& configurationString );

	virtual void Execute();

private:
	CActionNotifyIncomingSMS(const CActionNotifyIncomingSMS&);
	CActionNotifyIncomingSMS& operator=( const CActionNotifyIncomingSMS&);

private:
	IGSMActionContext& m_rGSMActionContext;
};
}
