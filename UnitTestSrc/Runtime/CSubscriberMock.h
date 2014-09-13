#ifndef RUNTIME_CSUBSCRIBERMOCK_H
#define RUNTIME_CSUBSCRIBERMOCK_H
#include <Runtime/ISubscriber.h>

namespace Runtime
{
class ISubscriberMockHelper;
class CMessage;

class CSubscriberMock : public ISubscriber
{
public:
	CSubscriberMock(ISubscriberMockHelper* pMockHelper);
	virtual ~CSubscriberMock();
	
	virtual void HandleMessage( CMessage& message );
	
private:
	CSubscriberMock(const CSubscriberMock&);
	CSubscriberMock& operator=(const CSubscriberMock&);
	
	ISubscriberMockHelper* m_pMockHelper;
};
}

#endif
