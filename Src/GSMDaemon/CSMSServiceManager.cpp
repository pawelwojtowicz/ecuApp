#include "CSMSServiceManager.h"
#include "IGSMDaemonConfiguration.h"
#include "IGSMModemService.h"
#include "Logger/Logger.h"


namespace GSMDaemon
{


CSMSServiceManager::CSMSServiceManager(	TTS::CTTSProxy& rTTSProxy)
: m_pModemService(0)
, m_rTTSProxy(rTTSProxy)

{
}

CSMSServiceManager::~CSMSServiceManager()
{
}

bool CSMSServiceManager::Initialize( const IGSMDaemonConfiguration& configuration, IGSMModemService* pModemService)
{
	configuration;
	m_pModemService = pModemService;

	if (0==m_pModemService)
	{
		return false;
	}

	m_pModemService->RegisterSMSServiceListener(this);

	return true;
}

void CSMSServiceManager::Shutdown()
{
	if (0!=	m_pModemService)
	{
		m_pModemService->UnregisterSMSServiceListener(this);
	}
}

void CSMSServiceManager::NotifySMSSendSuccess()
{
}

void CSMSServiceManager::NotifySMSSendFailure()
{
}

void CSMSServiceManager::NotifyIncomingSMS( const std::string& srcNumber, const std::string& timestamp, const std::string& messageText)
{
	RETAILMSG(INFO, ("CSMSServiceManager::NotifyIncomingSMS - [%s]", messageText.c_str()));
	m_rTTSProxy.Say(messageText);
}


}
