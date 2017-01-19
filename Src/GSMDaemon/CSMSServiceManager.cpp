#include "CSMSServiceManager.h"
#include "IGSMDaemonConfiguration.h"
#include "IGSMModemService.h"


namespace GSMDaemon
{


CSMSServiceManager::CSMSServiceManager()
: m_pModemService(0)
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
}


}
