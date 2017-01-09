#include "CGSMDaemon.h"
#include "IGSMModemService.h"

namespace GSMDaemon
{
CGSMDaemon::CGSMDaemon()
: Runtime::CRuntimeUnit("GSMDaemon", "GSMDQueue")
, m_daemonConfiguration()
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
	if ( m_daemonConfiguration.Initialize() )
	{
		bool initOK(false);
		initOK 	= m_pModemService->Initialize(m_daemonConfiguration);
		initOK &= m_modemManager.Initialize( m_daemonConfiguration, m_pModemService);
		initOK &= m_voiceServiceManager.Initialize( m_daemonConfiguration, m_pModemService );
		initOK &= m_smsServiceManager.Initialize( m_daemonConfiguration, m_pModemService);
	}
  CRuntimeUnit::Initialize();
  InitializeTimerManager();
}

void CGSMDaemon::Shutdown()
{
	m_smsServiceManager.Shutdown();
	m_voiceServiceManager.Shutdown();
	m_modemManager.Shutdown();
}

}
