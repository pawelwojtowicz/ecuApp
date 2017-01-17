#pragma once
#include <Global/GlobalTypes.h>
#include "IActionExecutionContext.h"
#include "IResponseTimeoutHandler.h"
#include "CATProtocolActionFactory.h"
#include <CSM/CStateMachine.h>
#include <Runtime/ITimerManager.h>
#include <Runtime/ITimerListener.h>
#include "CParameterBundle.h"

namespace CSM
{
class ICSMConfigurator;
class IActionFactory;
}

namespace ATProtocolEngine
{
class ISerializationEngine;
class ISerialPortHandler;

class CATProtocolEngine : public IActionExecutionContext
												, public IResponseTimeoutHandler
												, public Runtime::ITimerListener
{
public:
	CATProtocolEngine(	ISerializationEngine& serializationEngine,
											CSM::ICSMConfigurator& stateMachineConfigurator,
											ISerialPortHandler& rSerialPortHandler,
											Runtime::ITimerManager& rTimerManager );
	virtual ~CATProtocolEngine();


	bool Initialize();
	void Shutdown();

	void DispatchEvent( const std::string& eventName );

	void NotifyResponseReceived( const std::string& response );

	void NotifyPromptReceived(const std::string& prompt );

private:
	/** IActionExecutionContext implementation */
	virtual IResponseTimeoutHandler& GetTimeoutHandler();

	virtual ISerializationEngine& GetSerializationEngine();

	virtual ISerialPortHandler& GetSerialPortHandler();

	virtual CParameterBundle& GetParameterBundle();

private:
	/** IResponseTimeoutHandler implementation */
	virtual void StartTimeout( UInt32 timeout );

	virtual void StopTimeout();

protected:
	virtual void NotifyTimer( const Int32& timerId );

protected:
	Runtime::ITimerManager& GetTimerManager();

	void RegisterActionFactory( IATProtocolActionFactory& pATProtocolActionFactory );

private:
	ISerializationEngine& m_rSerializationEngine;

	CSM::ICSMConfigurator& m_rStateMachineConfigurator;

	CATProtocolActionFactory m_ATProtocolActionFactory;

	CSM::CStateMachine m_stateMachine;

	CParameterBundle m_parameterBundle;

	ISerialPortHandler& m_rSerialPortHandler;

	Runtime::ITimerManager& m_rTimerManager;

	Int32 m_atResponseTimeoutId;
};

}
