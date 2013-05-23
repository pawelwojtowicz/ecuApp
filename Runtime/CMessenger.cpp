#include "CMessenger.h"
#include "CMessage.h"
#include <fcntl.h>
#include <sys/stat.h>

CMessenger::CMessenger()
:m_run(true)
{
}

CMessenger::~CMessenger()
{
}

	//general initialization
bool CMessenger::Initialize(const std::string& componentName)
{
// create own message queue - R/W writes

// attach to broadast queue

// register broadcast queue
}

bool CMessenger::Shutdown()
{
// unregister broadcast queue

// deattach from broadcast queue

// dispose own queue
}

//initialization of the transmitter
bool CMessenger::ConnectQueue(const std::string& queueName)
{
	tQueueMapConstIter pCIter = m_queueName2QueueDescMap.find(queueName);
	if ( m_queueName2QueueDescMap.end() == pCIter )
	{
		mqd_t queueDescriptor = mq_open( queueName.str_c() , O_WRONLY );
		if ( -1 != queueDescriptor )
		{
			m_queueName2QueueDescMap.insert(tQueueName2QueueDescriptorMap::value_type(queueName,queueDescriptor));
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool CMessenger::DisconnectQueue(const std::string& queueName)
{
	tQueueMapIter pIter = m_queueName2QueueDescMap.find( queueName );
	if ( m_queueName2QueueDescMap.end() == pIter )
	{
		if ( mq_close( pIter->second )
		{
			m_queueName2QueueDescMap.erase(pIter);
			return true;
		}
	}
	return false;
}

//initialization of the receiver
bool CMessenger::SubscribeMessage( const int& msgId, ISubscriber* pSubscriber )
{
	if ( m_msgId2SubscriberMap.end() == m_msgId2SubscriberMap.find( msgId ) )
	{
		m_msgId2SubscriberMap.insert(tMsgId2SubscriberMap::value_type(msgId,pSubscriber));
		return true;
	}
	return false;
}

bool CMessenger::UnsubscribeMessage( const int& msgId, ISubscriber* pSubscriber )
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
	tQueueMapIter pIter = m_queueName2QueueDescMap.find( message.GetTargetName() );
	if ( m_queueName2QueueDescMap.end() != pIter )
	{
		if ( 0 == mq_send( pIter->second , message.GetBuffer() , message.GetSize(), message.GetPrio() ) )
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
		char[MSG_QUEUE] messageBuffer;
		size_t messageSize(0)

		do
		{
			messageSize = mq_receive( m_ownQueueDescriptor, messageBuffer, MSG_QUEUE, 0 );
			if ( messageSize > 0 )
			{
				CMessage message(messageBuffer, messageSize);
				if ( message.IsValid() )
				{
					tMsgId2SubscriberIterator pIter = m_msgId2SubscriberMap.find( message.GetMsgId() );
					if ( m_msgId2SubscriberMap.end() != pIter )
					{
						message.Reset()
						pIter->second->HandleMessage(message);
					}
				}				
			} 
		} while( m_run );
	}
}

