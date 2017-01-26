#include "CModemManager.h"
#include "IGSMDaemonConfiguration.h"
#include "IGSMModemService.h"
#include <Logger/Logger.h>

namespace GSMDaemon
{

CModemManager::CModemManager()
: m_pModemService(0)
{
}

CModemManager::~CModemManager()
{
}

bool CModemManager::Initialize( const IGSMDaemonConfiguration& configuration, IGSMModemService* pModemService)
{
	configuration;
	if (0==pModemService)
	{
		return false;
	}
	m_pModemService = pModemService;
	m_pModemService->RegisterModemListener(this);

	return true;
}

void CModemManager::Shutdown()
{
	m_pModemService->UnregisterModemListener(this);
}

void CModemManager::NotifyModemManufacturerReceived( const std::string& manufacturer )
{
	RETAILMSG(INFO, ("Modem manufacturer [%s]", manufacturer.c_str()));
}

void CModemManager::NotifyModemTypeReceived( const std::string& modemType )
{
	RETAILMSG(INFO, ("Modem type [%s]", modemType.c_str()));
}

void CModemManager::NotifyModemIMEIReceived( const std::string& IMEI )
{
	RETAILMSG(INFO, ("Modem IMEI [%s]", IMEI.c_str()));
}

void CModemManager::NotifySignalStrengthReceived ( const UInt32& signalStrength )
{
	RETAILMSG(INFO, ("Modem signal strength [%d]", signalStrength));
}

void CModemManager::NotifyGSMProviderNameReceived( const std::string& providerName )
{
	RETAILMSG(INFO, ("Provider name [%s]", providerName.c_str()));
}

void CModemManager::NotifyRegistrationStateReceived( const tNetworkRegistrationState& regState )
{
}

}
