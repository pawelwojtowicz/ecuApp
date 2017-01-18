#include "CGSMActionContext.h"
#include <GSMDaemon/IModemListener.h>
#include <GSMDaemon/IVoiceServiceListener.h>
#include <GSMDaemon/ISMSServiceListener.h>


namespace GSMModemSim800L
{
CGSMActionContext::CGSMActionContext()
: m_pModemListener(0)
, m_pVoiceServiceListener(0)
, m_pSMSServiceListener(0)
{
}

CGSMActionContext::~CGSMActionContext()
{
}

void CGSMActionContext::RegisterModemListener( GSMDaemon::IModemListener* pListener )
{
	m_pModemListener = pListener;
}

void CGSMActionContext::UnregisterModemListener( GSMDaemon::IModemListener* )
{
	m_pModemListener = 0;
}

void CGSMActionContext::RegisterVoiceServiceListener( GSMDaemon::IVoiceServiceListener* pVoiceServiceListener )
{
	m_pVoiceServiceListener = pVoiceServiceListener;
}

void CGSMActionContext::UnregisterVoiceServiceListener( GSMDaemon::IVoiceServiceListener* )
{
	m_pVoiceServiceListener = 0;
}

void CGSMActionContext::RegisterSMSServiceListener( GSMDaemon::ISMSServiceListener* pSMSServiceListener )
{
	m_pSMSServiceListener = pSMSServiceListener;
}

void CGSMActionContext::UnregisterSMSServiceListener( GSMDaemon::ISMSServiceListener* pSMSServiceListener )
{
	m_pSMSServiceListener = 0;
}

GSMDaemon::IModemListener* CGSMActionContext::GetModemListener() const
{
	return m_pModemListener;
}

GSMDaemon::IVoiceServiceListener* CGSMActionContext::GetVoiceServiceListener() const
{
	return m_pVoiceServiceListener;
}

GSMDaemon::ISMSServiceListener* CGSMActionContext::GetSMSServiceListener() const
{
	return m_pSMSServiceListener;
}

}
