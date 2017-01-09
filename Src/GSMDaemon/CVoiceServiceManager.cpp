#include "CVoiceServiceManager.h"
#include "IVoiceServiceListener.h"
#include "IGSMDaemonConfiguration.h"
#include "IGSMModemService.h"


namespace GSMDaemon
{


CVoiceServiceManager::CVoiceServiceManager()
: m_pModemService(0)
{
}

CVoiceServiceManager::~CVoiceServiceManager()
{
}

bool CVoiceServiceManager::Initialize( const IGSMDaemonConfiguration& configuration, IGSMModemService* pModemService)
{
	configuration;
	m_pModemService = pModemService;

	if (0==m_pModemService)
	{
		return false;
	}

	m_pModemService->RegisterVoiceServiceListener(this);

	return true;
}

void CVoiceServiceManager::Shutdown()
{
	if (0!=	m_pModemService)
	{
		m_pModemService->UnregisterVoiceServiceListener(this);
	}
}

void CVoiceServiceManager::NotifyBusy()
{
}

void CVoiceServiceManager::NotifyConnectionTerminated()
{
}

void CVoiceServiceManager::NotifyConnectionEstablished()
{
}

void CVoiceServiceManager::NotifyIncomingCall()
{
}

}
