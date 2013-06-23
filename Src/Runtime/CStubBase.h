#ifndef RUNTIME_CSTUBBASE_H
#define RUNTIME_CSTUBBASE_H
#include <GlobalTypes.h>
#include <RuntimeConst.h>
#include "ISubscriber.h"

namespace Runtime
{

class IMessenger;

class CStubBase : public ISubscriber
{
public:
	CStubBase( Runtime::IMessenger& rMessenger, const std::string& runtimeUnitName );
	virtual ~CStubBase();

	virtual bool Initialize();
	virtual bool Shutdown(); 

protected:
	Runtime::IMessenger& GetMessenger() { return m_rMessenger;};

	void SubscribeMessage(const tMsgIds& msgId );

private:
	CStubBase(const CStubBase&);
	CStubBase& operator=(const CStubBase&);

	Runtime::IMessenger& m_rMessenger;

	std::string m_runtimeUnitQueueName;
};
}
#endif
