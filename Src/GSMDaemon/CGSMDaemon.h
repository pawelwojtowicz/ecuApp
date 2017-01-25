#pragma once
#include <Runtime/CRuntimeUnit.h>
#include <GSMDaemonInterface/IGSMDaemonService.h>
#include "CGSMDaemonConfiguration.h"
#include <ATProtocolEngine/CSerialPortHandler.h>
#include "CModemManager.h"
#include "CVoiceServiceManager.h"
#include  "CSMSServiceManager.h"
#include <GSMDaemonInterface/CGSMDaemonStub.h>

namespace GSMDaemon
{
class IGSMModemService;

class CGSMDaemon : public Runtime::CRuntimeUnit, public IGSMDaemonService
{
public:
	CGSMDaemon();
	virtual ~CGSMDaemon();

	void Initialize();
	void Shutdown();

private:
	virtual void NotifyATResponseReceived( const std::string& response );
	virtual void NotifyATPromptReceived( const std::string& prompt ); 

private:
	CGSMDaemonConfiguration m_daemonConfiguration;

	ATProtocolEngine::CSerialPortHandler m_serialPortHandler;

	IGSMModemService* m_pModemService;

	CModemManager m_modemManager;

	CVoiceServiceManager m_voiceServiceManager;

	CSMSServiceManager m_smsServiceManager;

	CGSMDaemonStub m_gsmStub;
};
}
