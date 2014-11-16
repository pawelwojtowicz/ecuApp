#ifndef CONTROLLER_CCONTROLLER_H
#define CONTROLLER_CCONTROLLER_H

#include <stdio.h>
#include <GlobalTypes.h>
#include "Logger/CLogManager.h"
#include "Logger/CLoggingAgent.h"
#include "Runtime/CExecutable.h"
#include "Runtime/CMessenger.h"
#include "Runtime/ISubscriber.h"
#include "Runtime/CTimerManager.h"
#include "Runtime/CMessage.h"
#include "Runtime/ITimerListener.h"
#include "ControllerInterface/CControllerStub.h"
#include "ControllerInterface/IControllerServices.h"
#include "CWatchdogManager.h"
#include "CProcessManager.h"
#include "CSessionManager.h"

namespace Controller
{

class CController:	public IControllerServices, 
										public Runtime::CExecutable, 
										public Runtime::ITimerListener
{
	typedef enum
	{
		eWaitingForInit,
		eOperation,
		ePendingShutdown,
		eShutdown
	} tDeviceState;
public:
	CController();
	virtual ~CController() {};

	virtual void Initialize();
	virtual Int32 Run();
	virtual void Shutdown();

private:

	// implementation of Controller::IControllerServices
	virtual void NotifyUnitInitialized(	const UInt32& unitId, const std::string& processQueue, const std::string& unitVersion);
	virtual void NotifyUnitHeartbeat(	const UInt32 unitId, const Controller::tProcessStatus& status );


	virtual void NotifyShutdownRequest();
	virtual void NotifyRestartRequest();

	// Runtime infrastructure - handling of the timers - do not touch
	virtual void NotifyTimer();
	virtual void NotifyTimer( const Int32& timerId );

	Runtime::ITimerManager& GetTimerManager() { return m_timerManager; };
private:
	void ShutdownIfReady();
	
private:
	tDeviceState m_deviceState;

	Logger::CLogManager m_loggerManager;

	Logger::CLoggingAgent m_loggingAgent;

	Runtime::CMessenger m_messenger;

	Runtime::CTimerManager m_timerManager;

	Runtime::CMessage m_timerMessage;

	CControllerStub m_controllerStub;
	
	CSessionManager m_sessionManager;

	CWatchdogManager m_watchdogManager;

	CProcessManager m_processManager;
};

}

#endif
