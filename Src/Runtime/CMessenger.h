#ifndef RUNTIME_CMESSENGER_H
#define RUNTIME_CMESSENGER_H

#include <mqueue.h>
#include <map>
#include <set>
#include <string>
#include "GlobalTypes.h"
#include "RuntimeConst.h"
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
		UInt8 UsageCount;
	};

	// creates an association between QueueID and the QueueDetails structure. Used during PostingMessage
	// to select right Queue descriptor depending on the TargetId
	typedef std::map<Int32, QueueDetails> 							tQueueId2QueueDescriptorMap;
	typedef tQueueId2QueueDescriptorMap::const_iterator tQueueMapConstIter;
	typedef tQueueId2QueueDescriptorMap::iterator 			tQueueMapIter;

	// matches the MsgId with the subscriber.
	typedef std::map<tMsgIds, ISubscriber*> 			tMsgId2SubscriberMap;
	typedef tMsgId2SubscriberMap::iterator			  tMsgId2SubscriberIterator;
	typedef tMsgId2SubscriberMap::const_iterator 	tMsgId2SubscriberConstIterator;

	typedef std::set<Int32> tQueueIdSet;
	typedef tQueueIdSet::iterator tQueueIdSetIterator;
	typedef std::map<tMsgIds, tQueueIdSet> tMsgIdToInterestedQueues;
	typedef tMsgIdToInterestedQueues::iterator tMsgIdToInterestedQueuesIterator;
public:
	//construction/destruction
	CMessenger();
	virtual ~CMessenger();

	//general initialization
	bool Initialize(const std::string& runtimeUnitName);
	bool Shutdown();

	bool GetQueueParameters(Int32& maxNoMsg, Int32& maxMsgSize, Int32& currentQueueSize);
	bool SetQueueCapacity( const Int32& queueCapacity);
	bool SetMaxMessageSize( const Int32& maxMsgSize);

	//initialization of the transmitter
	Int32 ConnectQueue(const std::string& queueName);
	bool DisconnectQueue(const std::string& queueName);

	//initialization of the receiver
	bool SubscribeMessage( const Int32& supplierQueueId, const tMsgIds& msgId, ISubscriber* pSubscriber );
	bool UnsubscribeMessage( const Int32& supplierQueueId, const tMsgIds& msgId, ISubscriber* pSubscriber );

	//send message
	bool PostMessage( CMessage& message );

	void StartMsgProcessor();

	void StopMsgProcessor();

private:
	tQueueMapIter FindQueueByName( const std::string& queueName );

	bool PostSubscriptionMessage( const Int32& supplierQueueId, tMsgIds, bool subscribe );

private:
	tQueueId2QueueDescriptorMap m_queueName2QueueDescMap;

	tMsgId2SubscriberMap m_msgId2SubscriberMap;

	tMsgIdToInterestedQueues m_messageIdToQueueIdMap;

	bool m_run;

	UInt32 m_currentID;
	mqd_t m_ownQueueDescriptor;

};

}


#endif

