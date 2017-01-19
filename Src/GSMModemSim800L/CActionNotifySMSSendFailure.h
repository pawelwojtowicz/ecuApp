#pragma once
#include <ATProtocolEngine/CATProtocolAction.h>

namespace ATProtocolEngine
{
class IActionExecutionContext;
}

namespace GSMModemSim800L
{
class IGSMActionContext;

class CActionNotifySMSSendFailure : public ATProtocolEngine::CATProtocolAction
{
public:
	CActionNotifySMSSendFailure(IGSMActionContext& rGSMActionContext, ATProtocolEngine::IActionExecutionContext& rATPrtEngineContext);
	virtual ~CActionNotifySMSSendFailure();

	//virtual bool Configure( const CSM::IActionFactory& , const std::string& configurationString );

	virtual void Execute();

private:
	CActionNotifySMSSendFailure(const CActionNotifySMSSendFailure&);
	CActionNotifySMSSendFailure& operator=( const CActionNotifySMSSendFailure&);

private:
	IGSMActionContext& m_rGSMActionContext;
};
}
