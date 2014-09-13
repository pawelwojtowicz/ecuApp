#ifndef RUNTIME_ISubscriberMockHelper_H
#define RUNTIME_ISubscriberMockHelper_H
#include <gmock/gmock.h>

using ::testing::AtLeast;
using ::testing::Return;

namespace Runtime
{

class ISubscriberMockHelper
{
public:
	ISubscriberMockHelper() {};
	virtual ~ISubscriberMockHelper() {};
	
	virtual void TimerReceived() = 0;
	
private:
	ISubscriberMockHelper(const ISubscriberMockHelper&);
	ISubscriberMockHelper& operator=(const ISubscriberMockHelper&);
};

class SubscriberMock : public ISubscriberMockHelper 
{
public:
	MOCK_METHOD0(TimerReceived, void () );
};

}
#endif
