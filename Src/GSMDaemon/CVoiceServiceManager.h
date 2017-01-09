#pragma once
#include <Global/GlobalTypes.h>
#include "IVoiceServiceListener.h"

namespace GSMDaemon
{
class IGSMDaemonConfiguration;
class IGSMModemService;

class CVoiceServiceManager : public IVoiceServiceListener
{
public:
	CVoiceServiceManager();
	virtual ~CVoiceServiceManager();
	bool Initialize( const IGSMDaemonConfiguration& configuration, IGSMModemService* pModemService);
	void Shutdown();

private:
	/** implementation of IVoiceServiceListener*/
	virtual void NotifyBusy();
	virtual void NotifyConnectionTerminated();
	virtual void NotifyConnectionEstablished();
	virtual void NotifyIncomingCall();

private:
	IGSMModemService* m_pModemService;

};
}
