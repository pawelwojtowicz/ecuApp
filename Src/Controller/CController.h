#ifndef CONTROLLER_CCONTROLLER_H
#define CONTROLLER_CCONTROLLER_H

#include <stdio.h>
#include <GlobalTypes.h>
#include "Runtime/CExecutable.h"
#include "Runtime/CMessenger.h"
#include "Runtime/ISubscriber.h"
#include "Runtime/CTimerManager.h"
#include "Runtime/CMessage.h"
#include "ControllerInterface/CControllerStub.h"

namespace Controller
{

class CController: public Runtime::CExecutable
{
public:
	CController();
	virtual ~CController() {};

	virtual void Initialize();
	virtual Int32 Run();
	virtual void Shutdown();

private:
	virtual void NotifyTimer();
	

private:
	Runtime::CMessenger m_messenger;

	Runtime::CTimerManager m_timerManager;

	Runtime::CMessage m_timerMessage;

	CControllerStub m_controllerStub;
};

}

#endif
