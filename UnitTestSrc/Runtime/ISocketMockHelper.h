#ifndef UCL_ISocketMockHelper_H
#define UCL_ISocketMockHelper_H
#include <Global/RuntimeConst.h>
#include <gmock/gmock.h>

using ::testing::AtLeast;
using ::testing::Return;

namespace UCL
{

class ISocketMockHelper
{
public:
	ISocketMockHelper() {};
	virtual ~ISocketMockHelper(){};

	virtual void Bind(std::string queueName) = 0;
	virtual void Close() = 0;
	
	virtual void IsValid() = 0;
	
	virtual void IsEmpty() = 0;
	
	virtual void Send(std::string targetQueueName, tMsgIds msgId ) = 0;
	virtual void Receive() = 0;



private:
	ISocketMockHelper(const ISocketMockHelper&);
	ISocketMockHelper& operator=(const ISocketMockHelper&);
};

class UnixDomainSocketMock : public ISocketMockHelper 
{
public:
	MOCK_METHOD1(Bind, 		void ( std::string ) );
	MOCK_METHOD0(Close, 	void () );
  MOCK_METHOD2(Send,		void ( std::string , tMsgIds ) );
  MOCK_METHOD0(IsEmpty, void () );
  MOCK_METHOD0(IsValid, void () );
  MOCK_METHOD0(Receive, void () );
};

}

#endif
