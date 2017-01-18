#pragma once

namespace GSMDaemon
{
class IModemListener;
class IVoiceServiceListener;
class ISMSServiceListener;
}

namespace GSMModemSim800L
{
class IGSMActionContext
{
public:
	IGSMActionContext() {};
	virtual ~IGSMActionContext() {};

	virtual GSMDaemon::IModemListener* GetModemListener() const = 0;

	virtual GSMDaemon::IVoiceServiceListener* GetVoiceServiceListener() const = 0;

	virtual GSMDaemon::ISMSServiceListener* GetSMSServiceListener() const = 0;

private:
	IGSMActionContext( const IGSMActionContext&);
	IGSMActionContext& operator=(const IGSMActionContext&);
};
}
