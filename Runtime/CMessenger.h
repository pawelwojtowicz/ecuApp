#ifndef RUNTIME_CMESSENGER_H
#define RUNTIME_CMESSENGER_H

#include <mqueue.h>
#include <map>
#include <string>

namespace Runtime
{

class ISubscriber;
class CMessage;

class CMessenger
{
	typedef std::map<std::string, mqd_t> tQueueName2QueueDescriptorMap;
	typedef tQueueName2QueueDescriptor::const_iterator tQueueMapConstIter;
	typedef tQueueName2QueueDescriptor::iterator tQueueMapIter;

	typedef std::map<int, ISubscriber*> tMsgId2SubscriberMap;
	typedef tMsgId2SubscriberMap::iterator tMsgId2SubscriberIterator;
	typedef tMsgId2SubscriberMap::const_iterator tMsgId2SubscriberConstIterator;
public:
	//construction/destruction
	CMessenger();
	virtual ~CMessenger();

	//general initialization
	bool Initialize(const std::string& componentName);
	bool Shutdown();

	//initialization of the transmitter
	bool ConnectQueue(const std::string& queueName);
	bool DisconnectQueue(const std::string& queueName);

	//initialization of the receiver
	bool SubscribeMessage( const int& msgId, ISubscriber* pSubscriber );
	bool UnsubscribeMessage( const int& msgId, ISubscriber* pSubscriber );

	//send message
	bool PostMessage( const CMessage& message );

	void StartMsgProcessor();

private:
	tQueueName2QueueDescriptorMap m_queueName2QueueDescMap;

	tMsgId2SubscriberMap m_msgId2SubscriberMap;

	bool m_run;

	mqd_t m_ownQueueDescriptor;
};

}


#endif

