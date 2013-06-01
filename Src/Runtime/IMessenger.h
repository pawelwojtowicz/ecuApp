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

	//initialization of the transmitter
	UInt32 ConnectQueue(const std::string& queueName);
	bool DisconnectQueue(const std::string& queueName);

	//initialization of the receiver
	bool SubscribeMessage( const UInt32& msgId, ISubscriber* pSubscriber );
	bool UnsubscribeMessage( const UInt32& msgId, ISubscriber* pSubscriber );

	//send message
	bool PostMessage( const CMessage& message );

private:
	IMessenger& operator=(const IMessenger&);
	IMessenger(const IMessenger&);
};
}

#endif
