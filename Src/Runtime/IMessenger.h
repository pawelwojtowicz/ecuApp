#ifndef RUNTIME_IMESSENGER_H
#define RUNTIME_IMESSENGER_H

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
	virtual bool Initialize( const std::string& runtimeUnitQueueName) = 0;
	virtual bool Shutdown() = 0;
	//initialization of the transmitter
	virtual UInt32 ConnectQueue(const std::string& queueName) = 0;
	virtual bool DisconnectQueue(const std::string& queueName) = 0;

	//initialization of the receiver
	virtual bool SubscribeMessage( const UInt32& msgId, ISubscriber* pSubscriber ) = 0;
	virtual bool UnsubscribeMessage( const UInt32& msgId, ISubscriber* pSubscriber ) = 0;

	//send message
	virtual bool PostMessage( const CMessage& message ) = 0;

private:
	IMessenger& operator=(const IMessenger&);
	IMessenger(const IMessenger&);
};
}

#endif
