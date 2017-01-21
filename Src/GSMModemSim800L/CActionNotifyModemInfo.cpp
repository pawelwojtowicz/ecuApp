#include "CActionNotifyModemInfo.h"
#include <ATProtocolEngine/IActionExecutionContext.h>
#include "IGSMActionContext.h"
#include "GSMModemSim800LConst.h"
#include "GSMDaemon/ISMSServiceListener.h"
#include "GSMDaemon/IModemListener.h"
namespace GSMModemSim800L
{

CActionNotifyModemInfo::CActionNotifyModemInfo(const tModemInfoType infoType,IGSMActionContext& rGSMActionContext, ATProtocolEngine::IActionExecutionContext& rATPrtEngineContext)
: ATProtocolEngine::CATProtocolAction(rATPrtEngineContext)
, m_rGSMActionContext(rGSMActionContext)
, m_modemInfoType(infoType)
{

}

CActionNotifyModemInfo::~CActionNotifyModemInfo()
{
}

void CActionNotifyModemInfo::Execute()
{
	if ( 0 != m_rGSMActionContext.GetModemListener() )
	{
		if ( GetExecutionContext().GetParameterBundle().IsAvailable(sc_RAW_DATA) )
		{
			std::string info(GetExecutionContext().GetParameterBundle().GetParameter(sc_RAW_DATA));
			switch(m_modemInfoType)
			{
			case mdmManufacturer:
			{
				m_rGSMActionContext.GetModemListener()->NotifyModemManufacturerReceived( info );
			};break;
			case mdmTypeSeries:
			{
				m_rGSMActionContext.GetModemListener()->NotifyModemTypeReceived(info);
			};break;
			case mdmIMEI:
			{
				m_rGSMActionContext.GetModemListener()->NotifyModemIMEIReceived(info);
			};break;
			default:;
			};
		}
	}
}

}
