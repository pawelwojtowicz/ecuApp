#ifndef RUNTIME_CMESSENGER_H
#define RUNTIME_CMESSENGER_H

#include <mqueue.h>
#include <map>
#include <string>
#include "GlobalTypes.h"
#include "IMessenger.h"

namespace Runtime
{

class ISubscriber;
class CMessage;

class CMessenger
{
	struct QueueDetails
	{
		std::string QueueName;
		mqd_t QueueDescriptor;
		long MaxMsgs;
		long MaxMsgSize;
	};
	typedef std::map<UInt32, QueueDetails> tQueueName2QueueDescriptorMap;
	typedef tQueueName2QueueDescriptorMap::const_iterator tQueueMapConstIter;
	typedef tQueueName2QueueDescriptorMap::iterator tQueueMapIter;

	typedef std::map<UInt32, ISubscriber*> tMsgId2SubscriberMap;
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
	UInt32 ConnectQueue(const std::string& queueName);
	bool DisconnectQueue(const std::string& queueName);

	//initialization of the receiver
	bool SubscribeMessage( const UInt32& msgId, ISubscriber* pSubscriber );
	bool UnsubscribeMessage( const UInt32& msgId, ISubscriber* pSubscriber );

	//send message
	bool PostMessage( const CMessage& message );

	void StartMsgProcessor();

	void StopMsgProcessor();

private:
	tQueueMapIter FindQueueByName( const std::string& queueName ); 

private:
	tQueueName2QueueDescriptorMap m_queueName2QueueDescMap;

	tMsgId2SubscriberMap m_msgId2SubscriberMap;

	bool m_run;

	mqd_t m_ownQueueDescriptor;

	UInt32 m_currentID;
};

}


#endif

