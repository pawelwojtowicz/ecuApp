#include "CModemManager.h"
#include "IGSMDaemonConfiguration.h"
#include "IGSMModemService.h"

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

}
