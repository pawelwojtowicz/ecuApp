#include "CActionNotifySignalStrength.h"
#include <ATProtocolEngine/IActionExecutionContext.h>
#include "IGSMActionContext.h"
#include "GSMModemSim800LConst.h"
#include "GSMDaemon/IModemListener.h"
namespace GSMModemSim800L
{

CActionNotifySignalStrength::CActionNotifySignalStrength(IGSMActionContext& rGSMActionContext, ATProtocolEngine::IActionExecutionContext& rATPrtEngineContext)
: ATProtocolEngine::CATProtocolAction(rATPrtEngineContext)
, m_rGSMActionContext(rGSMActionContext)
{

}

CActionNotifySignalStrength::~CActionNotifySignalStrength()
{
}

void CActionNotifySignalStrength::Execute()
{
	if ( 0 != m_rGSMActionContext.GetModemListener() )
	{
		if ( GetExecutionContext().GetParameterBundle().IsAvailable(sc_CSQ_rssi) )
		{
			std::string info(GetExecutionContext().GetParameterBundle().GetParameter(sc_CSQ_rssi));

			UInt32 signalStrength(static_cast<UInt32>(atoi(info.c_str())));

			m_rGSMActionContext.GetModemListener()->NotifySignalStrengthReceived( signalStrength );
		}
	}
}

}
