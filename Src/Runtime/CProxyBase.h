#ifndef RUNTIME_CPROXYBASE_H
#define RUNTIME_CPROXYBASE_H
#include "IMessenger.h"
#include "ISubscriber.h"
#include <RuntimeConst.h>

namespace Runtime
{
class CProxyBase : public ISubscriber
{
public:
	CProxyBase(IMessenger& rMessenger, const std::string& queueName);
	virtual ~CProxyBase();

	virtual bool Initialize();

protected:
	IMessenger& GetMessenger() { return m_rMessenger; };

	virtual bool SubscribeMessage( const tMsgIds& msgId );

	virtual bool UnsubscribeMessage( const tMsgIds& msgId );

	virtual Int32 GetTargetQueueId() { return m_targetQueueId;};

private:
	virtual void HandleMessage(Runtime::CMessage& rMessage);

private:
	CProxyBase(const CProxyBase&);
	CProxyBase& operator=(const CProxyBase&);

	IMessenger& m_rMessenger;

	std::string m_queueName;

	Int32 m_targetQueueId;
};
}
#endif
