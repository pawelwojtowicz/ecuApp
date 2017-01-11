#pragma once
#include <Global/GlobalTypes.h>

namespace GSMDaemon
{
class IGSMDaemonConfiguration;
class IModemListener;
class IVoiceServiceListener;
class ISMSServiceListener;

class IGSMModemService
{
public:
	IGSMModemService() {};
	virtual ~IGSMModemService() {};

	virtual bool Initialize( IGSMDaemonConfiguration& configuration ) = 0;
	virtual void Shutdown() = 0;

	// modem management service
	virtual void RegisterModemListener( IModemListener* pListener ) = 0;
	virtual void UnregisterModemListener( IModemListener* pListener ) = 0;
	virtual void Connect() = 0;
	virtual void Disconnect() = 0;

	// voice service
	virtual void RegisterVoiceServiceListener( IVoiceServiceListener* pVoiceServiceListener ) = 0;
	virtual void UnregisterVoiceServiceListener( IVoiceServiceListener* pVoiceServiceListener ) = 0;
	virtual void MakeCall( const std::string& phoneNumber ) = 0;
	virtual void HangUp()  = 0;
	virtual void AcceptIncomingCall() = 0;
	virtual void RejectIncomingCall() = 0;

	// SMS service
	virtual void RegisterSMSServiceListener( ISMSServiceListener* pSMSServiceListener ) = 0;
	virtual void UnregisterSMSServiceListener( ISMSServiceListener* pSMSServiceListener ) = 0;
	virtual void SendSMS ( const std::string& phoneNumber, const std::string& text )  = 0;


private:
	IGSMModemService(const IGSMModemService&);
	IGSMModemService& operator=(const IGSMModemService&);
};
}
