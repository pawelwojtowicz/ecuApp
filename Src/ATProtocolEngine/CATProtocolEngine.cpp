#include "CATProtocolEngine.h"
#include "ISerializationEngine.h"
#include "ISerialPortHandler.h"
#include <CSM/ICSMConfigurator.h>
#include <CSM/IActionFactory.h>
#include "CATProtocolAction.h"

namespace ATProtocolEngine
{
CATProtocolEngine::CATProtocolEngine(	ISerializationEngine& serializationEngine,
																			CSM::ICSMConfigurator& stateMachineConfigurator,
																			ISerialPortHandler& rSerialPortHandler)
: m_rSerializationEngine(serializationEngine)
, m_rStateMachineConfigurator(stateMachineConfigurator)
, m_ATProtocolActionFactory(*this)
, m_rSerialPortHandler(rSerialPortHandler)
{
}

CATProtocolEngine::~CATProtocolEngine()
{
}

bool CATProtocolEngine::Initialize()
{
	bool retVal( m_stateMachine.Initialize(&m_rStateMachineConfigurator, &m_ATProtocolActionFactory) );

	return retVal;
}

void CATProtocolEngine::Shutdown()
{
}

IResponseTimeoutHandler& CATProtocolEngine::GetTimeoutHandler()
{
	return *this;
}

ISerializationEngine& CATProtocolEngine::GetSerializationEngine()
{
	return m_rSerializationEngine;
}

ISerialPortHandler& CATProtocolEngine::GetSerialPortHandler()
{
	return m_rSerialPortHandler;
}

CParameterBundle& CATProtocolEngine::GetParameterBundle()
{
	return m_parameterBundle;
}

void CATProtocolEngine::StartTimeout( UInt32 timeout )
{
	timeout;
}

void CATProtocolEngine::StopTimeout()
{
}

void CATProtocolEngine::NotifyResponseReceived( const std::string& response )
{
	std::string eventName(m_rSerializationEngine.Deserialize( response,  m_parameterBundle ) );
	if ( !eventName.empty() )
	{
		m_stateMachine.DispatchEvent(eventName);
	}
}

void CATProtocolEngine::NotifyPromptReceived(const std::string& prompt )
{
}


}
