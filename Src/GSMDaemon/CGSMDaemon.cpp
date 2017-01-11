#include "CGSMDaemon.h"
#include <Logger/Logger.h>
#include "IGSMModemService.h"
#include "GSMModemSim800L/CModemProtocolLogic.h"

// important - global instance of the new class
GSMDaemon::CGSMDaemon gs;

namespace GSMDaemon
{
CGSMDaemon::CGSMDaemon()
: Runtime::CRuntimeUnit("GSMDaemon", "GSMDQueue")
, m_daemonConfiguration()
, m_serialPortHandler()
, m_pModemService(0)
, m_modemManager()
, m_voiceServiceManager()
, m_smsServiceManager()
{
}

CGSMDaemon::~CGSMDaemon()
{
}

void CGSMDaemon::Initialize()
{
  CRuntimeUnit::Initialize();
  InitializeTimerManager();

	if ( !m_daemonConfiguration.Initialize() )
	{
		bool initOK(false);
		m_pModemService = new GSMModemSim800L::CModemProtocolLogic(m_serialPortHandler, GetTimerManager());
		initOK 	= m_pModemService->Initialize(m_daemonConfiguration);
		initOK &= m_modemManager.Initialize( m_daemonConfiguration, m_pModemService);
		initOK &= m_voiceServiceManager.Initialize( m_daemonConfiguration, m_pModemService );
		initOK &= m_smsServiceManager.Initialize( m_daemonConfiguration, m_pModemService);
	}

	RETAILMSG(INFO, ("GSMDaemon init almost done"));


	InitDone(true);
}

void CGSMDaemon::Shutdown()
{
	m_smsServiceManager.Shutdown();
	m_voiceServiceManager.Shutdown();
	m_modemManager.Shutdown();
}

}
