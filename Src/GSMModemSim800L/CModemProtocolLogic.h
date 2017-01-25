#pragma once
#include <ATProtocolEngine/CATProtocolEngine.h>
#include <GSMDaemon/IGSMModemService.h>
#include <CSM/CArgoConfigurator.h>
#include "CSim800LSerialization.h"
#include "CGSMActionContext.h"
#include "CGSMModemActionFactory.h"

namespace GSMModemSim800L
{
class CModemProtocolLogic : public ATProtocolEngine::CATProtocolEngine
													, public GSMDaemon::IGSMModemService 
{
public:
	CModemProtocolLogic(ATProtocolEngine::ISerialPortHandler& rSerialPortHandler,
											Runtime::ITimerManager& rTimerManager);
	virtual ~CModemProtocolLogic();

private:
	/** implementation of GSMDaemon::IGSMModemService */
	virtual bool Initialize( GSMDaemon::IGSMDaemonConfiguration& configuration );
	virtual void Shutdown();

	// modem management service
	virtual void RegisterModemListener( GSMDaemon::IModemListener* pListener );
	virtual void UnregisterModemListener( GSMDaemon::IModemListener* pListener );
	virtual void Connect();
	virtual void Disconnect();

	// voice service
	virtual void RegisterVoiceServiceListener( GSMDaemon::IVoiceServiceListener* pVoiceServiceListener );
	virtual void UnregisterVoiceServiceListener( GSMDaemon::IVoiceServiceListener* pVoiceServiceListener );
	virtual void MakeCall( const std::string& phoneNumber );
	virtual void HangUp();
	virtual void AcceptIncomingCall();
	virtual void RejectIncomingCall();

	// SMS service
	virtual void RegisterSMSServiceListener( GSMDaemon::ISMSServiceListener* pSMSServiceListener );
	virtual void UnregisterSMSServiceListener( GSMDaemon::ISMSServiceListener* pSMSServiceListener );
	virtual void SendSMS ( const std::string& phoneNumber, const std::string& text );

	virtual void NotifyATResponseReceived( const std::string& response );
	virtual void NotifyATPromptReceived(const std::string& prompt );


private:
	// UCL::ITimerListener implementation
	virtual void NotifyTimer( const Int32& timerId );


private:
	CModemProtocolLogic(const CModemProtocolLogic&);
	CModemProtocolLogic& operator=(const CModemProtocolLogic&);

	UInt32 m_pollingCyclePeriod;

	CSim800LSerialization m_serializationEngine;

	CSM::CArgoConfigurator m_csmConfigurator;

	Int32 m_pollingTimerId;

	CGSMActionContext m_actionExecutionContext;

	CGSMModemActionFactory m_actionFactory;
};
}
