#include "CMessenger.h"
#include "CMessage.h"
#include "ISubscriber.h"
#include <RuntimeConst.h>
#include <UCL/SystemEnvironment.h>
#include <stdio.h>


namespace Runtime
{

CMessenger::CMessenger(UCL::IUnixDomainSocket* pUnixDomainSocket)
: m_run( true )
, m_currentID( 2 ) // 0 = broadcast queue, 1 = own queue.
, m_pSocket(pUnixDomainSocket)
, m_externalSocket(true)
{
	if ( 0 == m_pSocket )
	{
		m_pSocket = new UCL::CUnixDomainSocket();
		m_externalSocket = false;
	}
}

CMessenger::~CMessenger()
{
	if ( !m_externalSocket )
	{
		delete m_pSocket;
	}
}

bool CMessenger::Initialize(const std::string& runtimeUnitName)
{
	bool retVal(false);
	
	std::string queueName(UCL::SystemEnvironment::ResolvePath(UCL::SystemEnvironment::Dir_Runtime,runtimeUnitName));

	retVal = m_pSocket->Bind( queueName );
	
	if ( retVal )
	{
		QueueInfo queueInfo;
		queueInfo.QueueName = queueName;
		queueInfo.Address= UCL::CSocketAddress(queueName);
		
		m_queueName2QueueDescMap.insert(tQueueId2QueueInfoMap::value_type(OWN_QUEUE_ID,queueInfo));
	}
	else
	{
		m_pSocket->Close();
	}

	return retVal;
}

bool CMessenger::Shutdown()
{
	m_pSocket->Close();
	m_queueName2QueueDescMap.clear();
	
	return true;
}

//initialization of the transmitter
Int32 CMessenger::ConnectQueue(const std::string& targetUnitName)
{
	Int32 queueID(-1);
	
	std::string queueName(UCL::SystemEnvironment::ResolvePath(UCL::SystemEnvironment::Dir_Runtime,targetUnitName));
	tQueueMapIter pIter = FindQueueByName(queueName);
	if ( m_queueName2QueueDescMap.end() == pIter )
	{
		QueueInfo queueInfo;
		queueInfo.QueueName = queueName;
		queueInfo.Address= UCL::CSocketAddress(queueName);
		queueInfo.RefCount = 1;
		queueID = m_currentID++;
		m_queueName2QueueDescMap.insert(tQueueId2QueueInfoMap::value_type(queueID,queueInfo));
	}
	else
	{
		++pIter->second.RefCount;
		queueID = pIter->first;
	}
	return queueID;
}

bool CMessenger::DisconnectQueue(const std::string& targetUnitName)
{
	std::string queueName(UCL::SystemEnvironment::ResolvePath(UCL::SystemEnvironment::Dir_Runtime,targetUnitName));

	tQueueMapIter pIter = FindQueueByName( queueName );
	if ( m_queueName2QueueDescMap.end() != pIter )
	{
		--pIter->second.RefCount;
		if ( 0 == pIter->second.RefCount )
		{
			m_queueName2QueueDescMap.erase(pIter);
		}
		return true;
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
					m_pSocket->Send(pIter->second.Address,message.GetBuffer() , message.GetBufferSize());
				}
			}
		}		
	}
	else
	{
		tQueueMapIter pIter = m_queueName2QueueDescMap.find( message.GetTargetId() );
		if ( m_queueName2QueueDescMap.end() != pIter )
		{
			if ( message.GetBufferSize() == m_pSocket->Send(pIter->second.Address,message.GetBuffer() , message.GetBufferSize()))
			{
				return true;
			}
		}
	}
	return false;
}

void CMessenger::StartMsgProcessor()
{
	if ( m_pSocket->IsValid() )
	{	
		char messageBuffer[MAX_MSG_SIZE];
		Int32 messageSize(0);
		UInt32 priority(0);
		UCL::CSocketAddress address;

		do
		{
			messageSize = m_pSocket->Receive(address, messageBuffer, MAX_MSG_SIZE );
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
#ifdef UNIT_TEST
						case msgId_InvalidMsgId:
						{
							m_run = false;
						};break;
#endif
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

bool CMessenger::PostSubscriptionMessage( const Int32 supplierQueueId, tMsgIds messageId, bool subscribe )
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

