#include "CProxyBase.h"

namespace Runtime
{
CProxyBase::CProxyBase(IMessenger& rMessenger, const std::string& queueName)
: m_rMessenger(rMessenger)
, m_queueName(queueName)
, m_targetQueueId(-1)
{
}

CProxyBase::~CProxyBase()
{
}

bool CProxyBase::Initialize()
{
	m_targetQueueId = m_rMessenger.ConnectQueue(m_queueName);
	
	return ( -1 != m_targetQueueId );
}

bool CProxyBase::SubscribeMessage( const tMsgIds& msgId )
{
	return m_rMessenger.SubscribeMessage( m_targetQueueId, msgId, this );
}

bool CProxyBase::UnsubscribeMessage( const tMsgIds& msgId )
{
	return m_rMessenger.UnsubscribeMessage( m_targetQueueId, msgId, this );
}

void CProxyBase::HandleMessage(Runtime::CMessage& rMessage)
{
	rMessage;
}



}
