#include "CATProtocolEngine.h"
#include "ISerializationEngine.h"
#include <CSM/ICSMConfigurator.h>
#include <CSM/IActionFactory.h>
#include "CATProtocolAction.h"

namespace ATProtocolEngine
{
CATProtocolEngine::CATProtocolEngine(	ISerializationEngine& serializationEngine,
																			CSM::ICSMConfigurator& stateMachineConfigurator)
: m_rSerializationEngine(serializationEngine)
, m_rStateMachineConfigurator(stateMachineConfigurator)
, m_ATProtocolActionFactory()
{
}

CATProtocolEngine::~CATProtocolEngine()
{
}

void CATProtocolEngine::RegisterATProtocolAction( const std::string& commandName, CATProtocolAction* pATProtocolAction)
{
	if ( !commandName.empty() && (0 != pATProtocolAction) )
	{
		pATProtocolAction->SetBundle(&m_parameterBundle);
		m_ATProtocolActionFactory.RegisterAction(commandName,pATProtocolAction);
	}
}

bool CATProtocolEngine::Initialize()
{
	bool retVal( m_stateMachine.Initialize(&m_rStateMachineConfigurator, &m_ATProtocolActionFactory) );

	return retVal;
}

void CATProtocolEngine::Shutdown()
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
