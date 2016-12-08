#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <CSM/IAction.h>
#include "ATProtocolEngineTestMocks.h"

#include <ATProtocolEngine/CATProtocolActionFactory.h>

TEST( CATProtocolActionFactory, NonExistingActionWillNotBeValid )
{
	CSerialPortHandlerMock serialPortMock;
	ATProtocolEngine::CParameterBundle paramBundleInstance;
	CSerializationEngineMock serializationEngineMock;
	ActionContextMock actionExecutionContextForTest(serialPortMock, paramBundleInstance, serializationEngineMock);

	ATProtocolEngine::CATProtocolActionFactory actionFactory(actionExecutionContextForTest);
	CSM::IActionFactory& CSM_ActionFactory(actionFactory);

	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "NonExisting" );

	// the action was NOT created
	ASSERT_TRUE( 0 == pAction );

}


TEST( CATProtocolActionFactory, SendCommand_DynamicallySerialized )
{
	CSerialPortHandlerMock serialPortMock;
	ATProtocolEngine::CParameterBundle paramBundleInstance;
	CSerializationEngineMock serializationEngineMock;
	ActionContextMock actionExecutionContextForTest(serialPortMock, paramBundleInstance, serializationEngineMock);

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

TEST( CATProtocolActionFactory, SendCommand_StaticMessage )
{
	CSerialPortHandlerMock serialPortMock;
	ATProtocolEngine::CParameterBundle paramBundleInstance;
	CSerializationEngineMock serializationEngineMock;
	ActionContextMock actionExecutionContextForTest(serialPortMock, paramBundleInstance, serializationEngineMock);

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

TEST( CATProtocolActionFactory, CCompositeAction )
{
	CSerialPortHandlerMock serialPortMock;
	ATProtocolEngine::CParameterBundle paramBundleInstance;
	CSerializationEngineMock serializationEngineMock;
	ActionContextMock actionExecutionContextForTest(serialPortMock, paramBundleInstance, serializationEngineMock);

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

