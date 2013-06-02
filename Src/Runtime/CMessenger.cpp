#include "CMessenger.h"
#include "CMessage.h"
#include "ISubscriber.h"
#include <RuntimeConst.h>
#include <fcntl.h>
#include <sys/stat.h>

#include <stdio.h>
#include <errno.h>
#include <string.h>

#define MSG_SIZE 256
#define BROADCAST_QUEUE_ID 0
#define OWN_QUEUE_ID 1

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

	m_ownQueueDescriptor = mq_open( runtimeUnitName.c_str() , O_RDWR|O_CREAT, S_IRWXU, NULL);
	if(-1 != m_ownQueueDescriptor)
	{
		// initialize the own QUEUE
		QueueDetails qd;
		qd.QueueName = runtimeUnitName;
		qd.QueueDescriptor = m_ownQueueDescriptor;
		m_queueName2QueueDescMap.insert(tQueueName2QueueDescriptorMap::value_type(OWN_QUEUE_ID,qd));

		// initialize the BROADCAST queue, all of the
		QueueDetails broadcastQueueDetails;
		broadcastQueueDetails.QueueName = std::string(s_BroadcastQueueName);
		broadcastQueueDetails.QueueDescriptor = mq_open( s_BroadcastQueueName , O_WRONLY|O_CREAT, S_IRWXU, NULL);
		if ( -1 != broadcastQueueDetails.QueueDescriptor)
		{
			m_queueName2QueueDescMap.insert(tQueueName2QueueDescriptorMap::value_type(BROADCAST_QUEUE_ID,broadcastQueueDetails) );
			retVal = true;
		}
	}

	return retVal;
}

bool CMessenger::Shutdown()
{
	bool retVal(false);
// unregister broadcast queue

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
			queueAttributes.mq_msgsize = maxMsgSize ;
			if ( 0 == mq_setattr(m_ownQueueDescriptor,&queueAttributes, NULL) )
			{
				retVal = true;
			}
		}
	}
	return retVal;
}


//initialization of the transmitter
UInt32 CMessenger::ConnectQueue(const std::string& queueName)
{
	UInt32 queueID(-1);
	tQueueMapConstIter pCIter = FindQueueByName(queueName);
	if ( m_queueName2QueueDescMap.end() == pCIter )
	{
		mqd_t queueDescriptor = mq_open( queueName.c_str() , O_WRONLY|O_CREAT, S_IRWXU, NULL);

		if ( -1 != queueDescriptor )
		{
			QueueDetails qd;
			qd.QueueName = queueName;
			qd.QueueDescriptor = queueDescriptor;

			queueID = m_currentID++;
			m_queueName2QueueDescMap.insert(tQueueName2QueueDescriptorMap::value_type(queueID,qd));
		}
	}
	else
	{
		queueID = pCIter->first;
	}
	return queueID;
}

bool CMessenger::DisconnectQueue(const std::string& queueName)
{
	tQueueMapIter pIter = FindQueueByName( queueName );
	if ( m_queueName2QueueDescMap.end() == pIter )
	{
		if ( mq_close( pIter->second.QueueDescriptor ) )
		{
			m_queueName2QueueDescMap.erase(pIter);
			return true;
		}
	}
	return false;
}

//initialization of the receiver
bool CMessenger::SubscribeMessage( const UInt32& msgId, ISubscriber* pSubscriber )
{
	if ( m_msgId2SubscriberMap.end() == m_msgId2SubscriberMap.find( msgId ) )
	{
		m_msgId2SubscriberMap.insert(tMsgId2SubscriberMap::value_type(msgId,pSubscriber));
		return true;
	}
	return false;
}

bool CMessenger::UnsubscribeMessage( const UInt32& msgId, ISubscriber* pSubscriber )
{
	tMsgId2SubscriberIterator pIter = m_msgId2SubscriberMap.find( msgId );
	if ( m_msgId2SubscriberMap.end() != pIter  )
	{
		m_msgId2SubscriberMap.erase(pIter);
		return true;
	}
	return false;
}

//send message
bool CMessenger::PostMessage( const CMessage& message )
{
	tQueueMapIter pIter = m_queueName2QueueDescMap.find( message.GetTargetId() );
	if ( m_queueName2QueueDescMap.end() != pIter )
	{
		if ( 0 == mq_send( pIter->second.QueueDescriptor , message.GetBuffer() , message.GetBufferSize(), message.GetMessagePrio() ) )
		{
			return true;
		}
	}
	return false;
}

void CMessenger::StartMsgProcessor()
{
	if ( -1 != m_ownQueueDescriptor )
	{	
		char messageBuffer[MSG_SIZE];
		size_t messageSize(0);
		UInt32 priority(0);

		do
		{
			messageSize = mq_receive( m_ownQueueDescriptor, messageBuffer, MSG_SIZE, &priority );
			if ( messageSize > 0 )
			{
				CMessage message(messageBuffer, messageSize);
				if ( message.IsValid() )
				{
					message.SetMsgPrio(static_cast<UInt8>(priority));
					tMsgId2SubscriberIterator pIter = m_msgId2SubscriberMap.find( message.GetMessageId() );
					if ( m_msgId2SubscriberMap.end() != pIter )
					{
						pIter->second->HandleMessage(message);
					}
				}				
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
}

