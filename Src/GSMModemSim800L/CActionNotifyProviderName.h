#pragma once
#include <ATProtocolEngine/CATProtocolAction.h>

namespace ATProtocolEngine
{
class IActionExecutionContext;
}

namespace GSMModemSim800L
{
class IGSMActionContext;

class CActionNotifyProviderName : public ATProtocolEngine::CATProtocolAction
{
public:
	CActionNotifyProviderName( IGSMActionContext& rGSMActionContext, ATProtocolEngine::IActionExecutionContext& rATPrtEngineContext);
	virtual ~CActionNotifyProviderName();

	//virtual bool Configure( const CSM::IActionFactory& , const std::string& configurationString );

	virtual void Execute();

private:
	CActionNotifyProviderName(const CActionNotifyProviderName&);
	CActionNotifyProviderName& operator=( const CActionNotifyProviderName&);

private:
	IGSMActionContext& m_rGSMActionContext;
};
}
