#pragma once
#include <ATProtocolEngine/CATProtocolAction.h>

namespace ATProtocolEngine
{
class IActionExecutionContext;
}

namespace GSMModemSim800L
{
class IGSMActionContext;

class CActionDetermineNextStep : public ATProtocolEngine::CATProtocolAction
{
public:
	CActionDetermineNextStep( IGSMActionContext& rGSMActionContext, ATProtocolEngine::IActionExecutionContext& rATPrtEngineContext);
	virtual ~CActionDetermineNextStep();

	//virtual bool Configure( const CSM::IActionFactory& , const std::string& configurationString );

	virtual void Execute();

private:
	CActionDetermineNextStep(const CActionDetermineNextStep&);
	CActionDetermineNextStep& operator=( const CActionDetermineNextStep&);

private:
	IGSMActionContext& m_rGSMActionContext;
};
}
