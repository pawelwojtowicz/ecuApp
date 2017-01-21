#pragma once
#include <GSMDaemon/ISMSServiceListener.h>
#include <GSMDaemon/IModemListener.h>

using ::testing::Return;
using ::testing::EndsWith;


class SMSServiceListenerMock: public GSMDaemon::ISMSServiceListener
{
public:

	MOCK_METHOD0( NotifySMSSendSuccess, void() );
	MOCK_METHOD0( NotifySMSSendFailure, void() );
	MOCK_METHOD3( NotifyIncomingSMS, void ( const std::string& srcNumber, const std::string& timestamp, const std::string& messageText) );
};

class ModemListenerMock : public GSMDaemon::IModemListener
{
public:
	MOCK_METHOD1(NotifyModemManufacturerReceived, void ( const std::string& manufacturer ) );
	MOCK_METHOD1(NotifyModemTypeReceived, void( const std::string& modemType ) );
	MOCK_METHOD1(NotifyModemIMEIReceived, void( const std::string& IMEI ) );

	MOCK_METHOD1(NotifySignalStrengthReceived, void( const UInt32& signalStrength )  );
	MOCK_METHOD1(NotifyGSMProviderNameReceived, void( const std::string& providerName ) );
	MOCK_METHOD1(NotifyRegistrationStateReceived, void( const GSMDaemon::tNetworkRegistrationState& regState ) );
};

