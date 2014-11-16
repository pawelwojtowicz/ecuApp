#ifndef RUNTIME_ITIMERMANAGER_H
#define RUNTIME_ITIMERMANAGER_H
#include "GlobalTypes.h"

namespace Runtime
{
class ITimerListener;

class ITimerManager
{
public:
	ITimerManager() {};
	virtual ~ITimerManager() {};

	// creates a timer - returns unique timerId
	virtual Int32 CreateTimer( ITimerListener* timerListener ) = 0;

	// destroys the timer, given by the timerId
	virtual void DisposeTimer(const Int32 timerId ) = 0;	

	// sets the parameters for the timer, given by timerId
	virtual bool SetTimer( const Int32 timerId, const UInt32 delay, const UInt32 period) = 0;
	
	// Starts the timer, given by the Id
	virtual bool StartTimer(const Int32 timerId ) = 0;
	
	// Stops the timer, given by the Id	
	virtual bool StopTimer(const Int32 timerId) = 0;
	
	virtual const UInt32 GetCurrentTime() = 0;
	
private:
	ITimerManager(const ITimerManager&);
	ITimerManager& operator=(const ITimerManager&);
};
}

#endif
