#ifndef CONTROLLER_CCONTROLLER_H
#define CONTROLLER_CCONTROLLER_H

#include <stdio.h>
#include <GlobalTypes.h>
#include "Runtime/CExecutable.h"
#include "Runtime/CMessenger.h"
#include "Runtime/ISubscriber.h"

class CController: public Runtime::CExecutable, public Runtime::ISubscriber
{
public:
	CController();
	~CController() {};
	virtual Int32 Run();

	virtual void HandleMessage( Runtime::CMessage& message );


private:
	Runtime::CMessenger m_messager; 

};

#endif
