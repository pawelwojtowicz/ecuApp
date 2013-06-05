#ifndef RUNTIME_CRUNTIMEUNIT_H
#define RUNTIME_CRUNTIMEUNIT_H
#include "CExecutable.h"
#include "CTimerManager.h"
#include "CMessage.h"
#include <stdio.h>

namespace Runtime
{
class CRuntimeUnit: public CExecutable
{
public:
	CRuntimeUnit( const std::string& runtimeUnitName, const std::string& runtimeUnitQueueName );
	virtual ~CRuntimeUnit();

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

	void InitializeTimerManager();

	ITimerManager& GetTimerManager() { return m_timerManager; };

	const std::string GetUnitQueueName() { return m_unitQueueName; };

private:
	CMessenger m_messenger;

	CTimerManager m_timerManager;

	CMessage m_timerMessage;

	std::string m_unitQueueName;

	Int32 m_unitReturnValue;
};

}
#endif
