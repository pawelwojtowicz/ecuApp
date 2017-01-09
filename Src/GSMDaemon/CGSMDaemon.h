#pragma once
#include <Runtime/CRuntimeUnit.h>
#include "CGSMDaemonConfiguration.h"
#include "CModemManager.h"
#include "CVoiceServiceManager.h"
#include  "CSMSServiceManager.h"

namespace GSMDaemon
{
class IGSMModemService;

class CGSMDaemon : public Runtime::CRuntimeUnit
{
public:
	CGSMDaemon();
	virtual ~CGSMDaemon();

	void Initialize();
	void Shutdown();

private:
	CGSMDaemonConfiguration m_daemonConfiguration;

	IGSMModemService* m_pModemService;

	CModemManager m_modemManager;

	CVoiceServiceManager m_voiceServiceManager;

	CSMSServiceManager m_smsServiceManager;
};
}
