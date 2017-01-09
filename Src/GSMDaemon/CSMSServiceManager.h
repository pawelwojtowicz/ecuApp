#pragma once
#include <Global/GlobalTypes.h>
#include "ISMSServiceListener.h"

namespace GSMDaemon
{
class IGSMDaemonConfiguration;
class IGSMModemService;

class CSMSServiceManager : public ISMSServiceListener
{
public:
	CSMSServiceManager();
	virtual ~CSMSServiceManager();
	bool Initialize( const IGSMDaemonConfiguration& configuration, IGSMModemService* pModemService);
	void Shutdown();

private:
	/** implementation of ISMSServiceListener*/
	virtual void NotifySMSSentSuccess();
	virtual void NotifySMSSentFailure();

	virtual void NotifyIncomingSMS( const std::string& srcNumber, const std::string& timestamp, const std::string& messageText);

private:
	IGSMModemService* m_pModemService;

};
}
