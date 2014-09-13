#include <gtest/gtest.h>
#include <Runtime/CMessenger.h>
#include <Runtime/CMessage.h>
#include <Runtime/ISubscriber.h>
std::string ownQueueName("ownQueue");
std::string receiverQueueName("receiverQueue");
std::string testQueue1name("TestQueue1");
std::string testQueue2name("TestQueue2");
std::string testQueue3name("TestQueue3");
std::string testQueue4name("TestQueue4");

class SampleReceiver: public Runtime::ISubscriber
{
public:

	SampleReceiver( int receiverId )
	: m_gotMessage(false)
	{
		char queueName[100];
		sprintf(queueName,"%s%d",receiverQueueName.c_str(),receiverId);
		m_queueName=queueName;
	}
	
	bool Init() 
	{ 
		return true; 
	}
	
	bool Shutdown()
	{
		return true; 
	};
	
	bool SubscribeTestMessage()
	{
		return true;
	};
	
	bool UnsubscribeTestMessage()
	{
		return true;
	};
	
	bool ClearGotFlag() 
	{
		m_gotMessage=false;
	};
	
  bool GetGotFlag()
  {
  	return m_gotMessage;
  }

private:
	virtual void HandleMessage( Runtime::CMessage& message )
	{
		
	}
private:
	std::string m_queueName;
	
	bool m_gotMessage;
};


TEST( CMessenger,ConnectQeue_Basic )
{
	Runtime::CMessenger messenger;
	
	messenger.Initialize(ownQueueName);
	
	Int32 testQueue1Id(0);
	Int32 testQueue2Id(0);
	Int32 testQueue3Id(0);
	Int32 testQueue4Id(0);
	
	testQueue1Id = messenger.ConnectQueue(testQueue1name);
	testQueue2Id = messenger.ConnectQueue(testQueue2name);
	testQueue3Id = messenger.ConnectQueue(testQueue3name);
	testQueue4Id = messenger.ConnectQueue(testQueue4name);


  EXPECT_NE( testQueue1Id, 1 );
	EXPECT_NE( testQueue2Id, 1 );
  EXPECT_NE( testQueue3Id, 1 );
  EXPECT_NE( testQueue4Id, 1 );
  EXPECT_EQ( testQueue1Id, messenger.ConnectQueue(testQueue1name) );
	EXPECT_EQ( testQueue2Id, messenger.ConnectQueue(testQueue2name) );
  EXPECT_EQ( testQueue3Id, messenger.ConnectQueue(testQueue3name) );
  EXPECT_EQ( testQueue4Id, messenger.ConnectQueue(testQueue4name) );

	messenger.Shutdown();

}

TEST( CMessenger,ConnectQeue_OwnQueue )
{
	Runtime::CMessenger messenger;
	messenger.Initialize(ownQueueName);
	
	messenger.ConnectQueue(testQueue1name);
	messenger.ConnectQueue(testQueue2name);
	messenger.ConnectQueue(testQueue3name);
	messenger.ConnectQueue(testQueue4name);


  EXPECT_EQ( 1, messenger.ConnectQueue(ownQueueName) );
  
	messenger.Shutdown();

}

TEST( CMessenger,ConnectQeue_RefCount )
{
	Runtime::CMessenger messenger;
	messenger.Initialize(ownQueueName);
	
	Int32 q1firstPassId = messenger.ConnectQueue(testQueue1name);
	messenger.ConnectQueue(testQueue2name);
	messenger.ConnectQueue(testQueue3name);
	messenger.ConnectQueue(testQueue4name);
	Int32 q1secondPassId = messenger.ConnectQueue(testQueue1name);

	messenger.DisconnectQueue(testQueue1name);
	Int32 q1thirdPassId = messenger.ConnectQueue(testQueue1name);

	messenger.DisconnectQueue(testQueue1name);
	messenger.DisconnectQueue(testQueue1name);

	Int32 q1fourthPassId = messenger.ConnectQueue(testQueue1name);
	Int32 q1fifthPassId = messenger.ConnectQueue(testQueue1name);

  EXPECT_EQ( q1firstPassId , q1secondPassId );
  EXPECT_EQ( q1firstPassId , q1thirdPassId );
  EXPECT_NE( q1thirdPassId , q1fourthPassId );
 	EXPECT_EQ( q1fourthPassId,q1fifthPassId );
  
	messenger.Shutdown();

}
