#include "CMessenger.h"
#include "CMessage.h"
#include "ISubscriber.h"
#include <RuntimeConst.h>
#include <fcntl.h>
#include <sys/stat.h>

#include <stdio.h>
#include <errno.h>
#include <string.h>


namespace Runtime
{

CMessenger::CMessenger()
: m_run( true )
, m_currentID( 2 ) // 0 = broadcast queue, 1 = own queue.
, m_ownQueueDescriptor(-1)
{
}

CMessenger::~CMessenger()
{
}

	//general initialization
bool CMessenger::Initialize(const std::string& runtimeUnitName)
{
	bool retVal(false);
// create own message queue - R/W writes

	mq_attr queueAttributes;
	queueAttributes.mq_flags = 0;
	queueAttributes.mq_maxmsg = MAX_QUEUE_SIZE;
	queueAttributes.mq_msgsize = MAX_MSG_SIZE;

  // set the umask suitable to be able to open the queues by other users ( ex. Apache plugins )
  mode_t omask;
  omask = umask(0);   /* use permissions as specified */
	m_ownQueueDescriptor = mq_open( runtimeUnitName.c_str() , O_RDWR|O_CREAT, 0666, &queueAttributes);

  //restore the original umask
  umask(omask);

	if(-1 != m_ownQueueDescriptor)
	{
		// initialize the own QUEUE
		QueueDetails qd;
		qd.QueueName = runtimeUnitName;
		qd.QueueDescriptor = m_ownQueueDescriptor;
		qd.UsageCount = 1;
		m_queueName2QueueDescMap.insert(tQueueId2QueueDescriptorMap::value_type(OWN_QUEUE_ID,qd));
		retVal = true;
	}
	else
	{
		printf("blad %s\n", strerror(errno));
	}

	return retVal;
}

bool CMessenger::Shutdown()
{
	bool retVal(false);
// unregister broadcast queue

	// trzeba zrobic unlink na kolejce
// deattach from broadcast queue

// dispose own queue
	return retVal;
}

bool CMessenger::GetQueueParameters(Int32& maxNoMsg, Int32& maxMsgSize, Int32& currentQueueSize)
{
	bool retVal(false);
	if ( -1 != m_ownQueueDescriptor )
	{
		mq_attr queueAttributes;
		if ( 0 == mq_getattr(m_ownQueueDescriptor,&queueAttributes) )
		{
			maxNoMsg = queueAttributes.mq_maxmsg;
			maxMsgSize = queueAttributes.mq_msgsize;
			currentQueueSize = queueAttributes.mq_curmsgs;
			retVal = true;
		}
	}

	return retVal;
}

bool CMessenger::SetQueueCapacity( const Int32& queueCapacity)
{
	bool retVal(false);
	if ( -1 != m_ownQueueDescriptor )
	{
		mq_attr queueAttributes;
		if ( 0 == mq_getattr(m_ownQueueDescriptor,&queueAttributes) )
		{
			queueAttributes.mq_maxmsg = queueCapacity ;
			if ( 0 == mq_setattr(m_ownQueueDescriptor,&queueAttributes , NULL) )
			{
				retVal = true;
			}
		}
	}
	return retVal;
}

bool CMessenger::SetMaxMessageSize( const Int32& maxMsgSize)
{
	bool retVal(false);
	if ( -1 != m_ownQueueDescriptor )
	{
		mq_attr queueAttributes;
		if ( 0 == mq_getattr(m_ownQueueDescriptor,&queueAttributes) )
		{
			queueAttributes.mq_msgsize = maxMsgSize ;// set the umask suitable to be able to open the queues by other users ( ex. Apache plugins )
			if ( 0 == mq_setattr(m_ownQueueDescriptor,&queueAttributes, NULL) )
			{
				retVal = true;
			}
		}
	}
	return retVal;
}


//initialization of the transmitter
Int32 CMessenger::ConnectQueue(const std::string& queueName)
{
	Int32 queueID(-1);
	tQueueMapIter pIter = FindQueueByName(queueName);
	if ( m_queueName2QueueDescMap.end() == pIter )
	{
		mq_attr queueAttributes;
		queueAttributes.mq_flags = 0;
		queueAttributes.mq_maxmsg = MAX_QUEUE_SIZE;
		queueAttributes.mq_msgsize = MAX_MSG_SIZE;

    // set the umask suitable to be able to open the queues by other users ( ex. Apache plugins )
    mode_t omask;
    omask = umask(0);   /* use permissions as specified */

		mqd_t queueDescriptor = mq_open( queueName.c_str() , O_WRONLY|O_CREAT|O_NONBLOCK, 0666, &queueAttributes);
    
    // restore the original umasl    
    umask(omask);

		if ( -1 != queueDescriptor )
		{
			QueueDetails qd;
			qd.QueueName = queueName;
			qd.QueueDescriptor = queueDescriptor;
			qd.UsageCount = 1;

			queueID = m_currentID++;
			m_queueName2QueueDescMap.insert(tQueueId2QueueDescriptorMap::value_type(queueID,qd));
		}
    else
    {
      printf("zjebane otwieranie kolejki\n");
      printf("blad %s\n", strerror(errno));
    }
	}
	else
	{
		++pIter->second.UsageCount;
		queueID = pIter->first;
	}
	return queueID;
}

bool CMessenger::DisconnectQueue(const std::string& queueName)
{
	tQueueMapIter pIter = FindQueueByName( queueName );
	if ( m_queueName2QueueDescMap.end() == pIter )
	{
			--pIter->second.UsageCount;
			if (pIter->second.UsageCount <= 0 )
			{
				if ( mq_close( pIter->second.QueueDescriptor ) )
				{
					m_queueName2QueueDescMap.erase(pIter);
				}
				return true;
			}
	}
	return false;
}

//initialization of the receiver
bool CMessenger::SubscribeMessage(  const Int32& supplierQueueId, const tMsgIds& msgId, ISubscriber* pSubscriber )
{
	if ( m_msgId2SubscriberMap.end() == m_msgId2SubscriberMap.find( msgId ) )
	{
		m_msgId2SubscriberMap.insert(tMsgId2SubscriberMap::value_type(msgId,pSubscriber));
		if ( supplierQueueId > OWN_QUEUE_ID )
		{
			PostSubscriptionMessage( supplierQueueId, msgId, true );
		}
		return true;
	}
	return false;
}

bool CMessenger::UnsubscribeMessage( const Int32& supplierQueueId,const tMsgIds& msgId, ISubscriber* pSubscriber )
{
	tMsgId2SubscriberIterator pIter = m_msgId2SubscriberMap.find( msgId );
	if ( m_msgId2SubscriberMap.end() != pIter  )
	{
		if ( supplierQueueId > OWN_QUEUE_ID )
		{
			PostSubscriptionMessage( supplierQueueId, msgId, false );
		}
		m_msgId2SubscriberMap.erase(pIter);
		return true;
	}
	return false;
}

//send message
bool CMessenger::PostMessage( CMessage& message )
{
	message.SerializeHeader();
	Int32 targetId(message.GetTargetId());
	if ( BROADCAST_QUEUE_ID == targetId )
	{
		tMsgIdToInterestedQueuesIterator msgSubscribersIter = m_messageIdToQueueIdMap.find(message.GetMessageId());
		if ( m_messageIdToQueueIdMap.end() != msgSubscribersIter )
		{
			tQueueIdSet& setOfQueueIds = msgSubscribersIter->second;
			for	(	tQueueIdSetIterator queueIdIter = setOfQueueIds.begin() ; 
						queueIdIter != setOfQueueIds.end() ; 
						++queueIdIter )
			{
				tQueueMapIter pIter = m_queueName2QueueDescMap.find( *queueIdIter );
				if ( m_queueName2QueueDescMap.end() != pIter )
				{
					mq_send( pIter->second.QueueDescriptor , message.GetBuffer() , message.GetBufferSize(), message.GetMessagePrio() );
				}
			}
		}		
	}
	else
	{
		tQueueMapIter pIter = m_queueName2QueueDescMap.find( message.GetTargetId() );
		if ( m_queueName2QueueDescMap.end() != pIter )
		{
			if ( 0 == mq_send( pIter->second.QueueDescriptor , message.GetBuffer() , message.GetBufferSize(), message.GetMessagePrio() ) )
			{
				return true;
			}
		}
	}
	return false;
}

void CMessenger::StartMsgProcessor()
{
	if ( -1 != m_ownQueueDescriptor )
	{	
		char messageBuffer[MAX_MSG_SIZE];
		Int32 messageSize(0);
		UInt32 priority(0);

		do
		{
			messageSize = mq_receive( m_ownQueueDescriptor, messageBuffer, MAX_MSG_SIZE, &priority );
			if ( messageSize > 0 )
			{
				CMessage message(messageBuffer, messageSize);
				if ( message.IsValid() )
				{
					message.DeserializeHeader();

					tMsgIds msgId = message.GetMessageId();
					switch ( msgId )
					{
						case msgId_Runtime_SubscribeMessage:
						{
							std::string interestedQueueName;
							UInt32 integerMsgId(0);	
							if ( message.GetValue( interestedQueueName ) && message.GetValue( integerMsgId ) )
							{
								tMsgIds messageId = static_cast<tMsgIds>(integerMsgId);
					
								// connect to queue (increase reference count in case it's used already
								Int32 queueId = ConnectQueue(interestedQueueName);

								// check if this message already exists in the map
								tMsgIdToInterestedQueuesIterator iter = m_messageIdToQueueIdMap.find(messageId);
								if (iter != m_messageIdToQueueIdMap.end() )
								{
									if ( iter->second.end() == iter->second.find( queueId ) )
									{
										iter->second.insert( queueId );
									}
									else
									{
										// it already exists in the set - do not add/decrease ref count.
										DisconnectQueue(interestedQueueName);
									}
								}
								else
								{
									// msg id not yet exists in the map - add complete element to the map.
									tQueueIdSet setForNewId;
									setForNewId.insert( queueId );
									m_messageIdToQueueIdMap.insert(tMsgIdToInterestedQueues::value_type(messageId, setForNewId) );
								}
							}
						};break;
						case msgId_Runtime_UnsubscribeMessage:
						{
						};break;

						default:
						{
							message.SetMsgPrio(static_cast<UInt8>(priority));
							tMsgId2SubscriberIterator pIter = m_msgId2SubscriberMap.find( msgId );
							if ( m_msgId2SubscriberMap.end() != pIter )
							{
								pIter->second->HandleMessage(message);
							}
						}
					}//switch
				}	//			
			} 
			else
			{
				printf("blad %s\n", strerror(errno));
			}
		} while( m_run );
	}
}

void CMessenger::StopMsgProcessor()
{
	m_run = false;
}

CMessenger::tQueueMapIter CMessenger::FindQueueByName( const std::string& queueName )
{
	for (tQueueMapIter iter = m_queueName2QueueDescMap.begin() ; iter != m_queueName2QueueDescMap.end() ; ++iter )
	{
		if (queueName == iter->second.QueueName )
		{
			return iter;
		}
	}

	return m_queueName2QueueDescMap.end();
}

bool CMessenger::PostSubscriptionMessage( const Int32& supplierQueueId, tMsgIds messageId, bool subscribe )
{
	tQueueMapConstIter pCIter = m_queueName2QueueDescMap.find(OWN_QUEUE_ID);
	if ( m_queueName2QueueDescMap.end() != pCIter )
	{
		CMessage subscriptionMessage( 100 );
		subscriptionMessage.SetMessageId(subscribe ? msgId_Runtime_SubscribeMessage : 																							 msgId_Runtime_UnsubscribeMessage);
		subscriptionMessage.SetTargetId(supplierQueueId);	
		subscriptionMessage.SetMsgPrio(255);

		//setup the payload
		subscriptionMessage.SetValue(pCIter->second.QueueName);
		UInt32 integerMsgId(static_cast<UInt32>(messageId));
		subscriptionMessage.SetValue(integerMsgId);

		return PostMessage(subscriptionMessage);
	}
	return false;
}

}

