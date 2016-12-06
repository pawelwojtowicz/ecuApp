#pragma once
#include <Global/GlobalTypes.h>
#include "CATProtocolActionFactory.h"
#include <CSM/CStateMachine.h>
#include "CParameterBundle.h"

namespace CSM
{
class ICSMConfigurator;
class IActionFactory;
}

namespace ATProtocolEngine
{
class ISerializationEngine;

class CATProtocolEngine
{
public:
	CATProtocolEngine(	ISerializationEngine& serializationEngine,
											CSM::ICSMConfigurator& stateMachineConfigurator );
	virtual ~CATProtocolEngine();

	void RegisterATProtocolAction( const std::string& commandName, CATProtocolAction* pATProtocolAction);

	bool Initialize();
	void Shutdown();

	void NotifyResponseReceived( const std::string& response );

	void NotifyPromptReceived(const std::string& prompt );

private:
	ISerializationEngine& m_rSerializationEngine;

	CSM::ICSMConfigurator& m_rStateMachineConfigurator;

	CATProtocolActionFactory m_ATProtocolActionFactory;

	CSM::CStateMachine m_stateMachine;

	CParameterBundle m_parameterBundle;
};

}
