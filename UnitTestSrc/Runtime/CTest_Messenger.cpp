#include <gtest/gtest.h>
#include <gmock/gmock.h>  // Brings in Google Mock.
#include <Runtime/CMessenger.h>
#include <Runtime/CMessage.h>
#include <Runtime/ISubscriber.h>
#include <UCL/SystemEnvironment.h>
#include "CUDSMockHelper.h"
#include "ISocketMockHelper.h"
#include "ISubscriberMockHelper.h"
#include "CSubscriberMock.h"
#include <gmock/gmock.h>

using ::testing::AtLeast;
using ::testing::Return;


std::string ownQueueName("ownQueue");
std::string receiverQueueName("receiverQueue");
std::string testQueue1name("TestQueue1");
std::string testQueue2name("TestQueue2");
std::string testQueue3name("TestQueue3");
std::string testQueue4name("TestQueue4");

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

//   EXPECT_CALL(mok, PierwszaMetoda()).Times(3).WillOnce(Return(0)).WillRepeatedly(Return(1));

TEST( CMessenger , Bind_Close )
{
	UCL::UnixDomainSocketMock UDSMock;
	UCL::CUDSMockHelper testSocket(&UDSMock);
	
	Runtime::CMessenger messenger(&testSocket);
	
	EXPECT_CALL(UDSMock, Bind(UCL::SystemEnvironment::ResolvePath(UCL::SystemEnvironment::Dir_Runtime,ownQueueName ) ) ).Times(1);
	EXPECT_CALL(UDSMock, Close() ).Times(1);
	
	messenger.Initialize(ownQueueName);
	messenger.Shutdown();
} 

TEST( CMessenger , Sending_ToMultipleQueues )
{
	UCL::UnixDomainSocketMock UDSMock;
	UCL::CUDSMockHelper testSocket(&UDSMock);
	
	Runtime::CMessenger messenger(&testSocket);
	EXPECT_CALL(UDSMock, Bind(UCL::SystemEnvironment::ResolvePath(UCL::SystemEnvironment::Dir_Runtime,ownQueueName ) ) ).Times(1);

	messenger.Initialize(ownQueueName);

	
	Int32 testQueue1Id(0);
	Int32 testQueue2Id(0);
	Int32 testQueue3Id(0);
	Int32 testQueue4Id(0);
	
	testQueue1Id = messenger.ConnectQueue(testQueue1name);
	testQueue2Id = messenger.ConnectQueue(testQueue2name);
	testQueue3Id = messenger.ConnectQueue(testQueue3name);
	testQueue4Id = messenger.ConnectQueue(testQueue4name);

	
	EXPECT_CALL(UDSMock, Send(UCL::SystemEnvironment::ResolvePath(UCL::SystemEnvironment::Dir_Runtime,testQueue4name ), msgId_Controller_InitDone ) ).Times(1);
	EXPECT_CALL(UDSMock, Send(UCL::SystemEnvironment::ResolvePath(UCL::SystemEnvironment::Dir_Runtime,testQueue3name), msgId_Controller_Heartbeat ) ).Times(1);
	EXPECT_CALL(UDSMock, Send(UCL::SystemEnvironment::ResolvePath(UCL::SystemEnvironment::Dir_Runtime,testQueue2name ), msgId_Controller_RestartRequest ) ).Times(1);
	EXPECT_CALL(UDSMock, Send(UCL::SystemEnvironment::ResolvePath(UCL::SystemEnvironment::Dir_Runtime,testQueue1name ), msgId_Controller_ShutdownRequest ) ).Times(1);
	EXPECT_CALL(UDSMock, Close() ).Times(1);
	
	{
		Runtime::CMessage testMsg(256);
		testMsg.SetMessageId(msgId_Controller_InitDone);
		testMsg.SetMsgPrio(255);
		testMsg.SetTargetId(testQueue4Id);
		
		messenger.PostMessage(testMsg);
	}

	{
		Runtime::CMessage testMsg(256);
		testMsg.SetMessageId(msgId_Controller_Heartbeat);
		testMsg.SetMsgPrio(255);
		testMsg.SetTargetId(testQueue3Id);
		
		messenger.PostMessage(testMsg);
	}

	{
		Runtime::CMessage testMsg(256);
		testMsg.SetMessageId(msgId_Controller_RestartRequest);
		testMsg.SetMsgPrio(255);
		testMsg.SetTargetId(testQueue2Id);
		
		messenger.PostMessage(testMsg);
	}

	{
		Runtime::CMessage testMsg(256);
		testMsg.SetMessageId(msgId_Controller_ShutdownRequest);
		testMsg.SetMsgPrio(255);
		testMsg.SetTargetId(testQueue1Id);
		
		messenger.PostMessage(testMsg);
	}
	
	messenger.Shutdown();
} 

TEST( CMessenger , Subscription_Msg )
{
	// instantiate the mocks
	UCL::UnixDomainSocketMock UDSMock;
	UCL::CUDSMockHelper testSocket(&UDSMock);

	EXPECT_CALL(UDSMock, Bind(UCL::SystemEnvironment::ResolvePath(UCL::SystemEnvironment::Dir_Runtime,ownQueueName ) ) ).Times(1);

	// initialize the messenger with the mocs
	Runtime::CMessenger messenger(&testSocket);
	messenger.Initialize(ownQueueName);
	
	// gets the QueueID
	Int32 testQueue1Id(0);	
	testQueue1Id = messenger.ConnectQueue(testQueue1name);

	// setup the GMOCK requirements
	EXPECT_CALL(UDSMock, Send(UCL::SystemEnvironment::ResolvePath(UCL::SystemEnvironment::Dir_Runtime,testQueue1name ), msgId_Runtime_SubscribeMessage ) ).Times(1);	
	EXPECT_CALL(UDSMock, Close() ).Times(1);

	// need non-zero pointer - won't use it	
	Runtime::ISubscriber* pSubscriber = reinterpret_cast<Runtime::ISubscriber*>(0x423423F);

	// check if the thing is sent correctly
	messenger.SubscribeMessage( testQueue1Id, msgId_Controller_Heartbeat, pSubscriber );

	// shutdown the messenger
	messenger.Shutdown();
} 

TEST( CMessenger, Receiving )
{
	// instantiate the mocks
	// Own Queue mock
	UCL::UnixDomainSocketMock UDSMock;
	UCL::CUDSMockHelper testSocket(&UDSMock);
	{
		Runtime::CMessage testMsg(0);
		testMsg.SetMessageId(msgId_Runtime_Timer_1000);
		testMsg.SetMsgPrio(255);
		testMsg.SetTargetId(1);

		testSocket.EnqueueTestMsg(testMsg);
	}
	testSocket.ResetMockState();
	
	//ReceiverMock
	Runtime::SubscriberMock subscriberMock;
	Runtime::CSubscriberMock subscriberMockHelper(&subscriberMock);
	
	EXPECT_CALL(UDSMock, Bind(UCL::SystemEnvironment::ResolvePath(UCL::SystemEnvironment::Dir_Runtime,ownQueueName ) ) ).Times(1);
	EXPECT_CALL(UDSMock, Receive() ).Times(2);
	EXPECT_CALL(UDSMock, IsValid() ).Times(1);

	// initialize the messenger with the mocs
	Runtime::CMessenger messenger(&testSocket);
	messenger.Initialize(ownQueueName);

	messenger.SubscribeMessage(0, msgId_Runtime_Timer_1000, &subscriberMockHelper);
	 
	EXPECT_CALL(subscriberMock,TimerReceived() ).Times(1);
	
	messenger.StartMsgProcessor();
	messenger.StopMsgProcessor();
	EXPECT_CALL(UDSMock, Close() ).Times(1);
	// shutdown the messenger
	messenger.Shutdown();
}

TEST( CMessenger, Broadcasting )
{
	// instantiate the mocks
	// Own Queue mock
	UCL::UnixDomainSocketMock UDSMock;
	UCL::CUDSMockHelper testSocket(&UDSMock);
	{
		Runtime::CMessage testMsg(200);
		testMsg.SetMessageId(msgId_Runtime_SubscribeMessage);
		testMsg.SetMsgPrio(255);
		testMsg.SetTargetId(1);
		testMsg.SetValue(UCL::SystemEnvironment::ResolvePath(UCL::SystemEnvironment::Dir_Runtime,testQueue1name));
		UInt32 integerMsgId(static_cast<UInt32>(msgId_Controller_Heartbeat));
		testMsg.SetValue(integerMsgId);

		testSocket.EnqueueTestMsg(testMsg);
	}
	
	{
		Runtime::CMessage testMsg(200);
		testMsg.SetMessageId(msgId_Runtime_SubscribeMessage);
		testMsg.SetMsgPrio(255);
		testMsg.SetTargetId(1);
		testMsg.SetValue(UCL::SystemEnvironment::ResolvePath(UCL::SystemEnvironment::Dir_Runtime,testQueue2name));
		UInt32 integerMsgId(static_cast<UInt32>(msgId_Controller_Heartbeat));
		testMsg.SetValue(integerMsgId);

		testSocket.EnqueueTestMsg(testMsg);
	}

	{
		Runtime::CMessage testMsg(200);
		testMsg.SetMessageId(msgId_Runtime_SubscribeMessage);
		testMsg.SetMsgPrio(255);
		testMsg.SetTargetId(1);
		testMsg.SetValue(UCL::SystemEnvironment::ResolvePath(UCL::SystemEnvironment::Dir_Runtime,testQueue3name));
		UInt32 integerMsgId(static_cast<UInt32>(msgId_Controller_Heartbeat));
		testMsg.SetValue(integerMsgId);

		testSocket.EnqueueTestMsg(testMsg);
	}
	
	{
		Runtime::CMessage testMsg(200);
		testMsg.SetMessageId(msgId_Runtime_SubscribeMessage);
		testMsg.SetMsgPrio(255);
		testMsg.SetTargetId(1);
		testMsg.SetValue(UCL::SystemEnvironment::ResolvePath(UCL::SystemEnvironment::Dir_Runtime,testQueue4name));
		UInt32 integerMsgId(static_cast<UInt32>(msgId_Controller_Heartbeat));
		testMsg.SetValue(integerMsgId);

		testSocket.EnqueueTestMsg(testMsg);
	}
	testSocket.ResetMockState();
	
	//ReceiverMock
	Runtime::SubscriberMock subscriberMock;
	Runtime::CSubscriberMock subscriberMockHelper(&subscriberMock);
	
	EXPECT_CALL(UDSMock, Bind(UCL::SystemEnvironment::ResolvePath(UCL::SystemEnvironment::Dir_Runtime,ownQueueName ) ) ).Times(1);
	EXPECT_CALL(UDSMock, Receive() ).Times(5);
	EXPECT_CALL(UDSMock, IsValid() ).Times(1);
	EXPECT_CALL(UDSMock, Send(UCL::SystemEnvironment::ResolvePath(UCL::SystemEnvironment::Dir_Runtime,testQueue1name ), msgId_Controller_Heartbeat ) ).Times(1);
	EXPECT_CALL(UDSMock, Send(UCL::SystemEnvironment::ResolvePath(UCL::SystemEnvironment::Dir_Runtime,testQueue2name ), msgId_Controller_Heartbeat ) ).Times(1);
	EXPECT_CALL(UDSMock, Send(UCL::SystemEnvironment::ResolvePath(UCL::SystemEnvironment::Dir_Runtime,testQueue3name ), msgId_Controller_Heartbeat ) ).Times(1);
	EXPECT_CALL(UDSMock, Send(UCL::SystemEnvironment::ResolvePath(UCL::SystemEnvironment::Dir_Runtime,testQueue4name ), msgId_Controller_Heartbeat ) ).Times(1);


	// initialize the messenger with the mocs
	Runtime::CMessenger messenger(&testSocket);
	messenger.Initialize(ownQueueName);

	messenger.StartMsgProcessor();
	messenger.StopMsgProcessor();
	
	{
		Runtime::CMessage testMsg(256);
		testMsg.SetMessageId(msgId_Controller_Heartbeat);
		testMsg.SetMsgPrio(255);
		testMsg.SetTargetId(BROADCAST_QUEUE_ID);
		
		messenger.PostMessage(testMsg);
	}	

	EXPECT_CALL(UDSMock, Close() ).Times(1);
	// shutdown the messenger
	messenger.Shutdown();
}
