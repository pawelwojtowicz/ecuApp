#ifndef RUNTIME_CTIMERMANAGER_H
#define RUNTIME_CTIMERMANAGER_H
#include <map>
#include "ITimerManager.h"
#include "ISubscriber.h"


namespace Runtime
{
class ITimerListener;

class CTimerManager	: public ITimerManager
										, public ISubscriber
{
	struct tTimerStruct
	{
		bool active;
		UInt32 timerDelay;
		UInt32 timerPeriod;
		UInt32 timerNextExpiration;
		ITimerListener* timerSubscriber;
	};
	typedef std::map<Int32,tTimerStruct> tTimerInfoMap;
	typedef tTimerInfoMap::iterator tTimerInfoIterator;
public:
	CTimerManager();
	virtual ~CTimerManager();

private:
	// creates a timer - returns unique timerId
	virtual Int32 CreateTimer( ITimerListener* timerListener );

	// destroys the timer, given by the timerId
	virtual void DisposeTimer(const Int32 timerId );	

	// sets the parameters for the timer, given by timerId
	virtual bool SetTimer( const Int32 timerId, const UInt32 delay, const UInt32 period);
	
	// Starts the timer, given by the Id
	virtual bool StartTimer(const Int32 timerId );
	
	// Stops the timer, given by the Id	
	virtual bool StopTimer(const Int32 timerId);

	// Receives the message notification from the queue - the timer message is being equeued with the highest
	// prio every 1s.
	virtual void HandleMessage( CMessage& message );

	virtual const UInt32 GetCurrentTime();

private:
	CTimerManager(const CTimerManager&);
	CTimerManager& operator=(CTimerManager&);

	tTimerInfoMap m_timerInfoMap;

	Int32 m_nextFreeTimerId;

};

}
#endif
