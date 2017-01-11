#include "CModemProtocolLogic.h"

namespace GSMModemSim800L
{
CModemProtocolLogic::CModemProtocolLogic(ATProtocolEngine::ISerialPortHandler& rSerialPortHandler, Runtime::ITimerManager& rTimerManager)
: ATProtocolEngine::CATProtocolEngine( m_serializationEngine, m_csmConfigurator ,rSerialPortHandler, rTimerManager)
, m_serializationEngine()
, m_csmConfigurator(std::string("File"), std::string("state"))
{
}

CModemProtocolLogic::~CModemProtocolLogic()
{
}

bool CModemProtocolLogic::Initialize( GSMDaemon::IGSMDaemonConfiguration& configuration )
{
	ATProtocolEngine::CATProtocolEngine::Initialize();
	return false;
}

void CModemProtocolLogic::Shutdown()
{
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


}
