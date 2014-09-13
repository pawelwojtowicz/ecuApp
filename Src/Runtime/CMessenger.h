#ifndef RUNTIME_CMESSENGER_H
#define RUNTIME_CMESSENGER_H

#include <map>
#include <set>
#include <string>
#include "GlobalTypes.h"
#include "RuntimeConst.h"
#include "IMessenger.h"
#include <UCL/CSocket.h>

namespace Runtime
{

class ISubscriber;
class CMessage;

class CMessenger : public IMessenger
{
	struct QueueInfo
	{
		std::string QueueName;
		UCL::CSocketAddress Address;
		UInt32 RefCount;
	};

	// creates an association between QueueID and the QueueDetails structure. Used during PostingMessage
	// to select right Queue descriptor depending on the TargetId
	typedef std::map<Int32, QueueInfo> tQueueId2QueueInfoMap;
	typedef tQueueId2QueueInfoMap::const_iterator tQueueMapConstIter;
	typedef tQueueId2QueueInfoMap::iterator 			tQueueMapIter;

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

	bool PostSubscriptionMessage( const Int32 supplierQueueId, tMsgIds, bool subscribe );

private:
	tQueueId2QueueInfoMap m_queueName2QueueDescMap;

	tMsgId2SubscriberMap m_msgId2SubscriberMap;

	tMsgIdToInterestedQueues m_messageIdToQueueIdMap;

	bool m_run;

	UInt32 m_currentID;
	
	UCL::CSocket m_socket;

};

}


#endif

