#pragma once
#include "IModemListener.h"

namespace GSMDaemon
{
class IGSMDaemonConfiguration;
class IGSMModemService;

class CModemManager : public IModemListener
{
public:
	CModemManager();
	virtual ~CModemManager();

	bool Initialize( const IGSMDaemonConfiguration& configuration, IGSMModemService* pModemService);
	void Shutdown();

	virtual void NotifyModemManufacturerReceived( const std::string& manufacturer );
	virtual void NotifyModemTypeReceived( const std::string& modemType );	
	virtual void NotifyModemIMEIReceived( const std::string& IMEI );

	virtual void NotifySignalStrengthReceived ( const UInt32& signalStrength );
	virtual void NotifyGSMProviderNameReceived( const std::string& providerName );
	virtual void NotifyRegistrationStateReceived( const tNetworkRegistrationState& regState );


private:
	IGSMModemService* m_pModemService;
};
}
