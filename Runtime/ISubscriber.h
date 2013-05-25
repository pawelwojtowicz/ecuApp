#ifndef RUNTIME_ISUBSCRIBER_H
#define RUNTIME_ISUBSCRIBER_H

namespace Runtime
{
class CMessage;

class ISubscriber
{
public:
	ISubscriber() {};
	~ISubscriber() {};
	
	virtual void HandleMessage( const CMessage& message ) = 0;
};
}

#endif
