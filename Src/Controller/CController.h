#ifndef CONTROLLER_CCONTROLLER_H
#define CONTROLLER_CCONTROLLER_H

#include <stdio.h>
#include <GlobalTypes.h>
#include "Runtime/CExecutable.h"
#include "Runtime/CMessenger.h"
#include "Runtime/ISubscriber.h"
#include "Runtime/CTimerManager.h"
#include "Runtime/CMessage.h"
#include "Runtime/ITimerListener.h"
#include "ControllerInterface/CControllerStub.h"
#include "ControllerInterface/IControllerServices.h"

namespace Controller
{

class CController:	public IControllerServices, 
										public Runtime::CExecutable, 
										public Runtime::ITimerListener
{
public:
	CController();
	virtual ~CController() {};

	virtual void Initialize();
	virtual Int32 Run();
	virtual void Shutdown();

private:

	// implementation of Controller::IControllerServices
	virtual void NotifyUnitInitialized(	const UInt32& unitId, 
																			const std::string& processQueue, 
																			const std::string& unitVersion);
	virtual void NotifyUnitHeartbeat(	const UInt32 unitId, 
																		const tProcessStatus& status );


	virtual void NotifyShutdownRequest();
	virtual void NotifyRestartRequest();

	// Runtime infrastructure - handling of the timers - do not touch
	virtual void NotifyTimer();
	virtual void NotifyTimer( const Int32& timerId );

	

	Runtime::ITimerManager& GetTimerManager() { return m_timerManager; };
	

private:
	Runtime::CMessenger m_messenger;

	Runtime::CTimerManager m_timerManager;

	Runtime::CMessage m_timerMessage;

	CControllerStub m_controllerStub;

	Int32 m_timer1Id;
	Int32 m_timer2Id;
};

}

#endif
