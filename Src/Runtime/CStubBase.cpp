#include "CStubBase.h"
#include "IMessenger.h"

namespace Runtime
{

CStubBase::CStubBase( Runtime::IMessenger& rMessenger, const std::string& runtimeUnitQueueName )
: m_rMessenger(rMessenger)
, m_runtimeUnitQueueName(runtimeUnitQueueName)
{
}


CStubBase::~CStubBase()
{
}

bool CStubBase::Initialize()
{
//Initialize own queue;
	m_rMessenger.Initialize(m_runtimeUnitQueueName);
	return true;
}

bool CStubBase::Shutdown()
{
	return true;
}

void CStubBase::HandleMessage(Runtime::CMessage& rMessage)
{
}

void CStubBase::SubscribeMessage(const tMsgIds& msgId )
{
	m_rMessenger.SubscribeMessage( OWN_QUEUE_ID, msgId, this );
}

}
