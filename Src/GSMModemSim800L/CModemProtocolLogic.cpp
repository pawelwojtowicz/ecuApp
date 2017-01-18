#include "CModemProtocolLogic.h"

namespace GSMModemSim800L
{
CModemProtocolLogic::CModemProtocolLogic(ATProtocolEngine::ISerialPortHandler& rSerialPortHandler, Runtime::ITimerManager& rTimerManager)
: ATProtocolEngine::CATProtocolEngine( m_serializationEngine, m_csmConfigurator ,rSerialPortHandler, rTimerManager)
, m_pollingCyclePeriod(30)
, m_serializationEngine()
, m_csmConfigurator(std::string("File"), std::string("state"))
, m_pollingTimerId(-1)
, m_actionExecutionContext()
, m_actionFactory(m_actionExecutionContext)
{
	RegisterActionFactory( m_actionFactory );
}

CModemProtocolLogic::~CModemProtocolLogic()
{
}

bool CModemProtocolLogic::Initialize( GSMDaemon::IGSMDaemonConfiguration& configuration )
{
	ATProtocolEngine::CATProtocolEngine::Initialize();

	m_pollingTimerId = GetTimerManager().CreateTimer(this);
	GetTimerManager().SetTimer(m_pollingTimerId,0, m_pollingCyclePeriod );
	GetTimerManager().StartTimer(m_pollingTimerId);

	return false;
}

void CModemProtocolLogic::Shutdown()
{
	GetTimerManager().StopTimer(m_pollingTimerId);
	GetTimerManager().DisposeTimer(m_pollingTimerId);

	CATProtocolEngine::Shutdown();
}

void CModemProtocolLogic::RegisterModemListener( GSMDaemon::IModemListener* pListener )
{
}

void CModemProtocolLogic::UnregisterModemListener( GSMDaemon::IModemListener* pListener )
{
}

void CModemProtocolLogic::Connect()
{
}

void CModemProtocolLogic::Disconnect()
{
}

void CModemProtocolLogic::RegisterVoiceServiceListener( GSMDaemon::IVoiceServiceListener* pVoiceServiceListener )
{
}

void CModemProtocolLogic::UnregisterVoiceServiceListener( GSMDaemon::IVoiceServiceListener* pVoiceServiceListener )
{
}

void CModemProtocolLogic::MakeCall( const std::string& phoneNumber )
{
}

void CModemProtocolLogic::HangUp()
{
}

void CModemProtocolLogic::AcceptIncomingCall()
{
}

void CModemProtocolLogic::RejectIncomingCall()
{
}

void CModemProtocolLogic::RegisterSMSServiceListener( GSMDaemon::ISMSServiceListener* pSMSServiceListener )
{
}

void CModemProtocolLogic::UnregisterSMSServiceListener( GSMDaemon::ISMSServiceListener* pSMSServiceListener )
{
}

void CModemProtocolLogic::SendSMS ( const std::string& phoneNumber, const std::string& text )
{
}

void CModemProtocolLogic::NotifyTimer( const Int32& timerId )
{
	if ( timerId == m_pollingTimerId )
	{
		DispatchEvent( "E_POLLING_TIMEOUT" );
	}
	else
	{
		ATProtocolEngine::CATProtocolEngine::NotifyTimer( timerId );
	}
}


}
