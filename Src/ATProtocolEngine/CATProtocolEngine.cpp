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
																			ISerialPortHandler& rSerialPortHandler,
																			Runtime::ITimerManager& rTimerManager)
: m_rSerializationEngine(serializationEngine)
, m_rStateMachineConfigurator(stateMachineConfigurator)
, m_ATProtocolActionFactory(*this)
, m_rSerialPortHandler(rSerialPortHandler)
, m_rTimerManager(rTimerManager)
, m_atResponseTimeoutId(-1)
{
}

CATProtocolEngine::~CATProtocolEngine()
{
}

bool CATProtocolEngine::Initialize()
{
	bool retVal( m_stateMachine.Initialize(&m_rStateMachineConfigurator, &m_ATProtocolActionFactory) );


	m_atResponseTimeoutId = m_rTimerManager.CreateTimer(this);

	return retVal;
}

void CATProtocolEngine::Shutdown()
{
	m_rTimerManager.DisposeTimer(m_atResponseTimeoutId);
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
	m_rTimerManager.SetTimer(m_atResponseTimeoutId,timeout,0);
	m_rTimerManager.StartTimer(m_atResponseTimeoutId);	
}

void CATProtocolEngine::StopTimeout()
{
	m_rTimerManager.StopTimer(m_atResponseTimeoutId);
}

void CATProtocolEngine::NotifyTimer( const Int32& timerId )
{
	if ( timerId == m_atResponseTimeoutId)
	{
		m_stateMachine.DispatchEvent("E_TIMEOUT");
	}
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

void CATProtocolEngine::DispatchEvent( const std::string& eventName )
{
	m_stateMachine.DispatchEvent(eventName);
}

Runtime::ITimerManager& CATProtocolEngine::GetTimerManager()
{
	return m_rTimerManager;
}


}
