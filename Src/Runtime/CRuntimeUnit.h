#ifndef RUNTIME_CRUNTIMEUNIT_H
#define RUNTIME_CRUNTIMEUNIT_H
#include "CExecutable.h"

namespace Runtime
{

class CRuntimeUnit: public CExecutable
{
public:

	//initialization of the unit
	virtual void Initialize();

	//main thread of the unit - meesage processor runs in this thread
	virtual Int32 Run();

	//called right before shutdown - release all the resources here
	virtual void Shutdown();

	//used implicitly by the timer - the method enqueues the timer messasges	
	virtual void NotifyTimer();

protected:
	IMessenger& GetMessenger();

private:
	CMessenger m_messenger;
};

}
#endif
