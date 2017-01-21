#pragma once
#include <ATProtocolEngine/CATProtocolAction.h>

namespace ATProtocolEngine
{
class IActionExecutionContext;
}

namespace GSMModemSim800L
{
class IGSMActionContext;

class CActionNotifyModemInfo : public ATProtocolEngine::CATProtocolAction
{
public:
	typedef enum
	{
		mdmManufacturer,
		mdmTypeSeries,
		mdmIMEI
	} tModemInfoType;
	CActionNotifyModemInfo( const tModemInfoType type, IGSMActionContext& rGSMActionContext, ATProtocolEngine::IActionExecutionContext& rATPrtEngineContext);
	virtual ~CActionNotifyModemInfo();

	//virtual bool Configure( const CSM::IActionFactory& , const std::string& configurationString );

	virtual void Execute();

private:
	CActionNotifyModemInfo(const CActionNotifyModemInfo&);
	CActionNotifyModemInfo& operator=( const CActionNotifyModemInfo&);

private:
	IGSMActionContext& m_rGSMActionContext;

	tModemInfoType m_modemInfoType;
};
}
