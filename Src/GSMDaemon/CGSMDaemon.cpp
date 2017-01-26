#include "CGSMDaemon.h"
#include <Logger/Logger.h>
#include "IGSMModemService.h"
#include "GSMModemSim800L/CModemProtocolLogic.h"
#include <GSMDaemonInterface/GSMDaemonInterfaceConst.h>

// important - global instance of the new class
GSMDaemon::CGSMDaemon gs;

namespace GSMDaemon
{
CGSMDaemon::CGSMDaemon()
: Runtime::CRuntimeUnit("GSMDaemon", s_GSMDaemonQueueName)
, m_daemonConfiguration()
, m_serialPortHandler()
, m_pModemService(0)
, m_modemManager()
, m_voiceServiceManager()
, m_ttsProxy(GetMessenger())
, m_smsServiceManager(m_ttsProxy)
, m_gsmStub(GetMessenger())
{
}

CGSMDaemon::~CGSMDaemon()
{
}

void CGSMDaemon::Initialize()
{
  CRuntimeUnit::Initialize();
  InitializeTimerManager();
	m_gsmStub.Initialize(this);
  m_ttsProxy.Initialize();


	if ( m_daemonConfiguration.Initialize() )
	{
		bool initOK(false);
		std::string portName("/dev/ttyUSB0");
		std::string portConfiguration("baud=115200 data=8 parity=none stop=1");
		m_serialPortHandler.Initialize( portName, portConfiguration );
		m_serialPortHandler.RegisterATLineConsumer(&m_gsmStub);
		m_pModemService = new GSMModemSim800L::CModemProtocolLogic(m_serialPortHandler, GetTimerManager());
		initOK 	= m_pModemService->Initialize(m_daemonConfiguration);
		RETAILMSG(INFO, ("Modem %d", initOK));
		initOK &= m_modemManager.Initialize( m_daemonConfiguration, m_pModemService);
		initOK &= m_voiceServiceManager.Initialize( m_daemonConfiguration, m_pModemService );
		initOK &= m_smsServiceManager.Initialize( m_daemonConfiguration, m_pModemService);

		m_pModemService->Connect();
	}

	RETAILMSG(INFO, ("GSMDaemon init almost done"));


	InitDone(true);
}

void CGSMDaemon::Shutdown()
{
	m_gsmStub.Shutdown();
	m_smsServiceManager.Shutdown();
	m_voiceServiceManager.Shutdown();
	m_modemManager.Shutdown();
}

void CGSMDaemon::NotifyATResponseReceived( const std::string& response )
{
	if (0!=m_pModemService)
	{
		m_pModemService->NotifyATResponseReceived( response );
//	void NotifyPromptReceived(const std::string& prompt );
	}
}

void CGSMDaemon::NotifyATPromptReceived( const std::string& prompt )
{
	if (0!=m_pModemService)
	{
		m_pModemService->NotifyATResponseReceived( prompt );
//	void NotifyPromptReceived(const std::string& prompt );
	}
}


}
