#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <CSM/IAction.h>
#include "ATProtocolEngineTestMocks.h"

#include <ATProtocolEngine/CATProtocolActionFactory.h>

TEST( CATProtocolActionFactory, NonExistingActionWillNotBeValid )
{
	CTimeoutHandlerMock timerHandlerMock;
	CSerialPortHandlerMock serialPortMock;
	ATProtocolEngine::CParameterBundle paramBundleInstance;
	CSerializationEngineMock serializationEngineMock;
	ActionContextMock actionExecutionContextForTest(timerHandlerMock,serialPortMock, paramBundleInstance, serializationEngineMock);

	ATProtocolEngine::CATProtocolActionFactory actionFactory(actionExecutionContextForTest);
	CSM::IActionFactory& CSM_ActionFactory(actionFactory);

	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "NonExisting" );

	// the action was NOT created
	ASSERT_TRUE( 0 == pAction );

}


TEST( CATProtocolActionFactory, SendCommand_DynamicallySerialized )
{
	CTimeoutHandlerMock timerHandlerMock;
	CSerialPortHandlerMock serialPortMock;
	ATProtocolEngine::CParameterBundle paramBundleInstance;
	CSerializationEngineMock serializationEngineMock;
	ActionContextMock actionExecutionContextForTest(timerHandlerMock,serialPortMock, paramBundleInstance, serializationEngineMock);

	ATProtocolEngine::CATProtocolActionFactory actionFactory(actionExecutionContextForTest);
	CSM::IActionFactory& CSM_ActionFactory(actionFactory);

	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "send(AT+CALL)" );

	// the action was created
	ASSERT_TRUE( 0 != pAction );

	// prepare the parameters for calling the execute
	paramBundleInstance.Store("outputValue", "exampleTelegram");
	paramBundleInstance.Store("status", "true");

	EXPECT_CALL(serialPortMock, Test_SendCommand(	EndsWith("exampleTelegram") )).Times(1);

	// fire the action
	pAction->Execute();

	EXPECT_EQ( serializationEngineMock.SerializeMsgID , std::string("AT+CALL"));

}

TEST( CATProtocolActionFactory, SendLineCommand_DynamicallySerialized )
{
	CTimeoutHandlerMock timerHandlerMock;
	CSerialPortHandlerMock serialPortMock;
	ATProtocolEngine::CParameterBundle paramBundleInstance;
	CSerializationEngineMock serializationEngineMock;
	ActionContextMock actionExecutionContextForTest(timerHandlerMock,serialPortMock, paramBundleInstance, serializationEngineMock);

	ATProtocolEngine::CATProtocolActionFactory actionFactory(actionExecutionContextForTest);
	CSM::IActionFactory& CSM_ActionFactory(actionFactory);

	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "sendLine(AT+CALL)" );

	// the action was created
	ASSERT_TRUE( 0 != pAction );

	// prepare the parameters for calling the execute
	paramBundleInstance.Store("outputValue", "exampleTelegram");
	paramBundleInstance.Store("status", "true");

	EXPECT_CALL(serialPortMock, Test_SendCommand(	EndsWith("exampleTelegram\r") )).Times(1);

	// fire the action
	pAction->Execute();

	EXPECT_EQ( serializationEngineMock.SerializeMsgID , std::string("AT+CALL"));

}

TEST( CATProtocolActionFactory, SendCommand_StaticMessage )
{
	CTimeoutHandlerMock timerHandlerMock;
	CSerialPortHandlerMock serialPortMock;
	ATProtocolEngine::CParameterBundle paramBundleInstance;
	CSerializationEngineMock serializationEngineMock;
	ActionContextMock actionExecutionContextForTest(timerHandlerMock,serialPortMock, paramBundleInstance, serializationEngineMock);

	ATProtocolEngine::CATProtocolActionFactory actionFactory(actionExecutionContextForTest);
	CSM::IActionFactory& CSM_ActionFactory(actionFactory);

	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "send(AT+CALL)" );

	// the action was created
	ASSERT_TRUE( 0 != pAction );


	// prepare the parameters for calling the execute
	paramBundleInstance.Store("outputValue", "exampleTelegram");
	paramBundleInstance.Store("status", "false");

	EXPECT_CALL(serialPortMock, Test_SendCommand(	EndsWith("AT+CALL") )).Times(1);

	pAction->Execute();

	EXPECT_EQ( serializationEngineMock.SerializeMsgID , std::string("AT+CALL"));

}

TEST( CATProtocolActionFactory, SendLineCommand_StaticMessage )
{
	CTimeoutHandlerMock timerHandlerMock;
	CSerialPortHandlerMock serialPortMock;
	ATProtocolEngine::CParameterBundle paramBundleInstance;
	CSerializationEngineMock serializationEngineMock;
	ActionContextMock actionExecutionContextForTest(timerHandlerMock,serialPortMock, paramBundleInstance, serializationEngineMock);

	ATProtocolEngine::CATProtocolActionFactory actionFactory(actionExecutionContextForTest);
	CSM::IActionFactory& CSM_ActionFactory(actionFactory);

	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "sendLine(AT+CALL)" );

	// the action was created
	ASSERT_TRUE( 0 != pAction );


	// prepare the parameters for calling the execute
	paramBundleInstance.Store("outputValue", "exampleTelegram");
	paramBundleInstance.Store("status", "false");

	EXPECT_CALL(serialPortMock, Test_SendCommand(	EndsWith("AT+CALL\r") )).Times(1);

	pAction->Execute();

	EXPECT_EQ( serializationEngineMock.SerializeMsgID , std::string("AT+CALL"));

}


TEST( CATProtocolActionFactory, CCompositeAction )
{
	CTimeoutHandlerMock timerHandlerMock;
	CSerialPortHandlerMock serialPortMock;
	ATProtocolEngine::CParameterBundle paramBundleInstance;
	CSerializationEngineMock serializationEngineMock;
	ActionContextMock actionExecutionContextForTest(timerHandlerMock,serialPortMock, paramBundleInstance, serializationEngineMock);

	ATProtocolEngine::CATProtocolActionFactory actionFactory(actionExecutionContextForTest);
	CSM::IActionFactory& CSM_ActionFactory(actionFactory);

	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "send(AT+CALL);send(AT+PAPA);send(AT+XXX)" );

	// the action was created
	ASSERT_TRUE( 0 != pAction );


	// prepare the parameters for calling the execute
	paramBundleInstance.Store("outputValue", "exampleTelegram");
	paramBundleInstance.Store("status", "false");

	EXPECT_CALL(serialPortMock, Test_SendCommand(	EndsWith("AT+CALL") )).Times(1);
	EXPECT_CALL(serialPortMock, Test_SendCommand(	EndsWith("AT+PAPA") )).Times(1);
	EXPECT_CALL(serialPortMock, Test_SendCommand(	EndsWith("AT+XXX") )).Times(1);
	
	pAction->Execute();

}

TEST( CATProtocolActionFactory, StartTimeout )
{
	CTimeoutHandlerMock timerHandlerMock;
	CSerialPortHandlerMock serialPortMock;
	ATProtocolEngine::CParameterBundle paramBundleInstance;
	CSerializationEngineMock serializationEngineMock;
	ActionContextMock actionExecutionContextForTest(timerHandlerMock,serialPortMock, paramBundleInstance, serializationEngineMock);

	ATProtocolEngine::CATProtocolActionFactory actionFactory(actionExecutionContextForTest);
	CSM::IActionFactory& CSM_ActionFactory(actionFactory);

	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "startTimer(5)" );

	// the action was created
	ASSERT_TRUE( 0 != pAction );


	EXPECT_CALL(timerHandlerMock, StartTimeout(	5 )).Times(1);
	
	pAction->Execute();

}

TEST( CATProtocolActionFactory, StopTimeout )
{
	CTimeoutHandlerMock timerHandlerMock;
	CSerialPortHandlerMock serialPortMock;
	ATProtocolEngine::CParameterBundle paramBundleInstance;
	CSerializationEngineMock serializationEngineMock;
	ActionContextMock actionExecutionContextForTest(timerHandlerMock,serialPortMock, paramBundleInstance, serializationEngineMock);

	ATProtocolEngine::CATProtocolActionFactory actionFactory(actionExecutionContextForTest);
	CSM::IActionFactory& CSM_ActionFactory(actionFactory);

	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "stopTimer()" );

	// the action was created
	ASSERT_TRUE( 0 != pAction );


	EXPECT_CALL(timerHandlerMock, StopTimeout( )).Times(1);
	
	pAction->Execute();

}


TEST( CATProtocolActionFactory, Store )
{
	CTimeoutHandlerMock timerHandlerMock;
	CSerialPortHandlerMock serialPortMock;
	ATProtocolEngine::CParameterBundle paramBundleInstance;
	CSerializationEngineMock serializationEngineMock;
	ActionContextMock actionExecutionContextForTest(timerHandlerMock,serialPortMock, paramBundleInstance, serializationEngineMock);

	ATProtocolEngine::CATProtocolActionFactory actionFactory(actionExecutionContextForTest);
	CSM::IActionFactory& CSM_ActionFactory(actionFactory);

	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "store(param1,param2)" );

	// the action was created
	ASSERT_TRUE( 0 != pAction );

	paramBundleInstance.Store("param1", "testingStoreAction");

	ASSERT_FALSE (  paramBundleInstance.IsAvailable("param2") );
		
	pAction->Execute();

	ASSERT_TRUE (  paramBundleInstance.IsAvailable("param2") );
	EXPECT_EQ ( std::string("testingStoreAction") , paramBundleInstance.GetParameter("param2") );

}


TEST( CATProtocolActionFactory, OpenPort )
{
	CTimeoutHandlerMock timerHandlerMock;
	CSerialPortHandlerMock serialPortMock;
	ATProtocolEngine::CParameterBundle paramBundleInstance;
	CSerializationEngineMock serializationEngineMock;
	ActionContextMock actionExecutionContextForTest(timerHandlerMock,serialPortMock, paramBundleInstance, serializationEngineMock);

	ATProtocolEngine::CATProtocolActionFactory actionFactory(actionExecutionContextForTest);
	CSM::IActionFactory& CSM_ActionFactory(actionFactory);

	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "openPort()" );

	// the action was created
	ASSERT_TRUE( 0 != pAction );
	EXPECT_CALL(serialPortMock, OpenPort()).Times(1);

	// fire the action
	pAction->Execute();

}

TEST( CATProtocolActionFactory, ClosePort )
{
	CTimeoutHandlerMock timerHandlerMock;
	CSerialPortHandlerMock serialPortMock;
	ATProtocolEngine::CParameterBundle paramBundleInstance;
	CSerializationEngineMock serializationEngineMock;
	ActionContextMock actionExecutionContextForTest(timerHandlerMock,serialPortMock, paramBundleInstance, serializationEngineMock);

	ATProtocolEngine::CATProtocolActionFactory actionFactory(actionExecutionContextForTest);
	CSM::IActionFactory& CSM_ActionFactory(actionFactory);

	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "closePort()" );

	// the action was created
	ASSERT_TRUE( 0 != pAction );
	EXPECT_CALL(serialPortMock, ClosePort()).Times(1);

	// fire the action
	pAction->Execute();

}

TEST( CATProtocolActionFactory, StartProcessing )
{
	CTimeoutHandlerMock timerHandlerMock;
	CSerialPortHandlerMock serialPortMock;
	ATProtocolEngine::CParameterBundle paramBundleInstance;
	CSerializationEngineMock serializationEngineMock;
	ActionContextMock actionExecutionContextForTest(timerHandlerMock,serialPortMock, paramBundleInstance, serializationEngineMock);

	ATProtocolEngine::CATProtocolActionFactory actionFactory(actionExecutionContextForTest);
	CSM::IActionFactory& CSM_ActionFactory(actionFactory);

	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "start()" );

	// the action was created
	ASSERT_TRUE( 0 != pAction );
	EXPECT_CALL(serialPortMock, StartProcessing()).Times(1);

	// fire the action
	pAction->Execute();

}

TEST( CATProtocolActionFactory, StopProcessing )
{
	CTimeoutHandlerMock timerHandlerMock;
	CSerialPortHandlerMock serialPortMock;
	ATProtocolEngine::CParameterBundle paramBundleInstance;
	CSerializationEngineMock serializationEngineMock;
	ActionContextMock actionExecutionContextForTest(timerHandlerMock,serialPortMock, paramBundleInstance, serializationEngineMock);

	ATProtocolEngine::CATProtocolActionFactory actionFactory(actionExecutionContextForTest);
	CSM::IActionFactory& CSM_ActionFactory(actionFactory);

	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "stop()" );

	// the action was created
	ASSERT_TRUE( 0 != pAction );
	EXPECT_CALL(serialPortMock, StopProcessing()).Times(1);

	// fire the action
	pAction->Execute();

}

