#pragma once
#include <ATProtocolEngine/CATProtocolAction.h>

namespace ATProtocolEngine
{
class IActionExecutionContext;
}

namespace GSMModemSim800L
{
class IGSMActionContext;

class CActionNotifySMSSent : public ATProtocolEngine::CATProtocolAction
{
public:
	CActionNotifySMSSent(IGSMActionContext& rGSMActionContext, ATProtocolEngine::IActionExecutionContext& rATPrtEngineContext);
	virtual ~CActionNotifySMSSent();

	//virtual bool Configure( const CSM::IActionFactory& , const std::string& configurationString );

	virtual void Execute();

private:
	CActionNotifySMSSent(const CActionNotifySMSSent&);
	CActionNotifySMSSent& operator=( const CActionNotifySMSSent&);

private:
	IGSMActionContext& m_rGSMActionContext;
};
}
