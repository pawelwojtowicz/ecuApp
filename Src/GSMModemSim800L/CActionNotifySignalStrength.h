#pragma once
#include <ATProtocolEngine/CATProtocolAction.h>

namespace ATProtocolEngine
{
class IActionExecutionContext;
}

namespace GSMModemSim800L
{
class IGSMActionContext;

class CActionNotifySignalStrength : public ATProtocolEngine::CATProtocolAction
{
public:
	CActionNotifySignalStrength( IGSMActionContext& rGSMActionContext, ATProtocolEngine::IActionExecutionContext& rATPrtEngineContext);
	virtual ~CActionNotifySignalStrength();

	//virtual bool Configure( const CSM::IActionFactory& , const std::string& configurationString );

	virtual void Execute();

private:
	CActionNotifySignalStrength(const CActionNotifySignalStrength&);
	CActionNotifySignalStrength& operator=( const CActionNotifySignalStrength&);

private:
	IGSMActionContext& m_rGSMActionContext;
};
}
