#ifndef RUNTIME_IMESSENGER_H
#define RUNTIME_IMESSENGER_H
#include <GlobalTypes.h>
#include <RuntimeConst.h>

namespace Runtime
{

class CMessage;
class ISubscriber;

class IMessenger
{
public:
	IMessenger() {};
	virtual ~IMessenger() {};

public:
	//initialization of the transmitter
	virtual UInt32 ConnectQueue(const std::string& queueName) = 0;
	virtual bool DisconnectQueue(const std::string& queueName) = 0;

	//initialization of the receiver
	virtual bool SubscribeMessage( const Int32& supplierQueueId, const tMsgIds& msgId, ISubscriber* pSubscriber ) = 0;
	virtual bool UnsubscribeMessage( const Int32& supplierQueueId, const tMsgIds& msgId, ISubscriber* pSubscriber ) = 0;

	//send message
	virtual bool PostMessage( const CMessage& message ) = 0;

private:
	IMessenger& operator=(const IMessenger&);
	IMessenger(const IMessenger&);
};
}

#endif
