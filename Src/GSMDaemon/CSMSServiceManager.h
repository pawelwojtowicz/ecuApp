#pragma once
#include <Global/GlobalTypes.h>
#include "ISMSServiceListener.h"
#include <TTSInterface/CTTSProxy.h>

namespace GSMDaemon
{
class IGSMDaemonConfiguration;
class IGSMModemService;

class CSMSServiceManager : public ISMSServiceListener
{
public:
	CSMSServiceManager(TTS::CTTSProxy & rProxy);
	virtual ~CSMSServiceManager();
	bool Initialize( const IGSMDaemonConfiguration& configuration, IGSMModemService* pModemService);
	void Shutdown();

private:
	/** implementation of ISMSServiceListener*/
	virtual void NotifySMSSendSuccess( const UInt32 messageId );
	virtual void NotifySMSSendFailure( const UInt32 messageId );

	virtual void NotifyIncomingSMS( const std::string& srcNumber, const std::string& timestamp, const std::string& messageText);

private:
	IGSMModemService* m_pModemService;

	TTS::CTTSProxy& m_rTTSProxy;
};
}
