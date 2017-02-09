#pragma once
#include "IGSMActionContext.h"


namespace GSMModemSim800L
{
class CGSMActionContext : public IGSMActionContext
{
public:
	CGSMActionContext(CSMSOutbox& smsOutbox);
	virtual ~CGSMActionContext();

	virtual void RegisterModemListener( GSMDaemon::IModemListener* pListener );
	virtual void UnregisterModemListener( GSMDaemon::IModemListener* pListener );

	virtual void RegisterVoiceServiceListener( GSMDaemon::IVoiceServiceListener* pVoiceServiceListener );
	virtual void UnregisterVoiceServiceListener( GSMDaemon::IVoiceServiceListener* pVoiceServiceListener );

	virtual void RegisterSMSServiceListener( GSMDaemon::ISMSServiceListener* pSMSServiceListener );
	virtual void UnregisterSMSServiceListener( GSMDaemon::ISMSServiceListener* pSMSServiceListener );

	GSMDaemon::IModemListener* GetModemListener() const;

	GSMDaemon::IVoiceServiceListener* GetVoiceServiceListener() const;

	GSMDaemon::ISMSServiceListener* GetSMSServiceListener() const;

	virtual CSMSOutbox& GetSMSOutbox() const;


private:
	CGSMActionContext( const CGSMActionContext&);
	CGSMActionContext& operator=(const CGSMActionContext&);

private:
	GSMDaemon::IModemListener* m_pModemListener;

	GSMDaemon::IVoiceServiceListener* m_pVoiceServiceListener;

	GSMDaemon::ISMSServiceListener* m_pSMSServiceListener;

	CSMSOutbox& m_rSMSOutbox;
};
}
