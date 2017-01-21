#pragma once

namespace GSMDaemon
{
class IVoiceServiceListener
{
public:
	IVoiceServiceListener() {};
	virtual ~IVoiceServiceListener() {};

	virtual void NotifyBusy() = 0;
	virtual void NotifyConnectionTerminated() = 0;
	virtual void NotifyConnectionEstablished() = 0;

	virtual void NotifyIncomingCall() = 0;

	virtual void NotifyIncomingCallNumber( const std::string& number) = 0;
	
private:
	IVoiceServiceListener(IVoiceServiceListener&);
	IVoiceServiceListener& operator=(const IVoiceServiceListener&);
};
}
