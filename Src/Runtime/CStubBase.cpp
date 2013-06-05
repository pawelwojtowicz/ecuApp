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
	m_rMessenger.Initialize(m_runtimeUnitQueueName);
//Initialize own queue;
	return true;
}

bool CStubBase::Shutdown()
{
	return true;
}

}