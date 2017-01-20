#pragma once
#include <Global/GlobalTypes.h>
#include "GSMDaemonTypes.h"

namespace GSMDaemon
{
class IModemListener
{
public:
	IModemListener() {};
	virtual ~IModemListener() {};

	virtual void NotifyModemManufacturerReceived( const std::string& manufacturer ) = 0;
	virtual void NotifyModemTypeReceived( const std::string& modemType ) = 0;	
	virtual void NotifyModemIMEIReceived( const std::string& IMEI ) = 0;

	virtual void NotifySignalStrengthReceived ( const UInt32& signalStrength ) = 0;
	virtual void NotifyGSMProviderNameReceived( const std::string& providerName ) = 0;
	virtual void NotifyRegistrationStateReceived( const tNetworkRegistrationState& regState ) = 0;
	
private:
	IModemListener(const IModemListener&);
	IModemListener& operator=(const IModemListener&);
};
}
