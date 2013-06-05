#ifndef RUNTIME_ITIMERLISTENER_H
#define RUNTIME_ITIMERLISTENER_H

namespace Runtime
{
class ITimerListener
{
public:
	ITimerListener() {};
	virtual ~ITimerListener() {};

	// notifies when the timer, given by the timerId, signalizes it's event
	virtual void NotifyTimer( const Int32& timerId ) = 0;

private:
	ITimerListener( const ITimerListener& );
	ITimerListener& operator= (const ITimerListener&);
};
}
#endif
