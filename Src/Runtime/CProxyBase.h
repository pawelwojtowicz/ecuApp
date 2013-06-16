#ifndef RUNTIME_CPROXYBASE_H
#define RUNTIME_CPROXYBASE_H
#include "IMessenger.h"
#include <RuntimeConst.h>

namespace Runtime
{
class CProxyBase
{
public:
	CProxyBase(IMessenger& rMessenger, const std::string& queueName)
	: m_rMessenger(rMessenger)
	, m_targetQueueId(m_rMessenger.ConnectQueue(queueName))
	{
	};

	virtual ~CProxyBase()
	{
	};

	virtual bool SubscribeMessage( const tMsgIds& msgId, ISubscriber* pSubscriber )
	{
		return m_rMessenger.SubscribeMessage( m_targetQueueId, msgId, pSubscriber );
	};

	virtual bool UnsubscribeMessage( const Int32& supplierQueueId, const tMsgIds& msgId, ISubscriber* pSubscriber )
	{
		return m_rMessenger.UnsubscribeMessage( m_targetQueueId, msgId, pSubscriber );
	};

protected:
	IMessenger& GetMessenger() { return m_rMessenger; };

private:
	CProxyBase(const CProxyBase&);
	CProxyBase& operator=(const CProxyBase&);

	IMessenger& m_rMessenger;

	Int32 m_targetQueueId;
};
}
#endif
