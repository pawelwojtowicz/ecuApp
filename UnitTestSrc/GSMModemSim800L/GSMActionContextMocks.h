#pragma once
#include <GSMDaemon/ISMSServiceListener.h>
#include <GSMDaemon/IModemListener.h>
#include <GSMDaemon/IVoiceServiceListener.h>
#include <GSMDaemon/IGSMDaemonConfiguration.h>
using ::testing::Return;
using ::testing::EndsWith;
using ::testing::NotNull;


class SMSServiceListenerMock: public GSMDaemon::ISMSServiceListener
{
public:

	MOCK_METHOD1( NotifySMSSendSuccess, void( const UInt32 msgId ) );
	MOCK_METHOD1( NotifySMSSendFailure, void( const UInt32 msgId ) );
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

class VoiceServiceListenerMock: public GSMDaemon::IVoiceServiceListener
{
public:
	MOCK_METHOD0( NotifyBusy, void() );
	MOCK_METHOD0( NotifyConnectionTerminated, void() );
	MOCK_METHOD0( NotifyConnectionEstablished, void() );

	MOCK_METHOD0( NotifyIncomingCall, void() );

	MOCK_METHOD1( NotifyIncomingCallNumber, void( const std::string& number) );
	MOCK_METHOD1( NotifyDTMFCode, void( const std::string& code ) );
};

class GSMConfiguration : public GSMDaemon::IGSMDaemonConfiguration
{
public:
};

