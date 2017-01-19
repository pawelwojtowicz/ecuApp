#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <GSMModemSim800L/CGSMModemActionFactory.h>
#include <GSMModemSim800L/CGSMActionContext.h>
#include <ATProtocolEngine/CParameterBundle.h>
#include "../ATProtocolEngine/ATProtocolEngineTestMocks.h"

#include <ATProtocolEngine/CATProtocolActionFactory.h>
#include "GSMActionContextMocks.h"
#include <CSM/IAction.h>

class GSMMModemActionFactoryFixture: public ::testing::Test
{
public:
	GSMMModemActionFactoryFixture()
	: timerHandlerMock()
	, serialPortMock()
	, paramBundleInstance()
	, serializationEngineMock()
	, actionExecutionContextForTest(timerHandlerMock,serialPortMock, paramBundleInstance, serializationEngineMock)
	, ATProtocolActionFactory(actionExecutionContextForTest)
	, CSM_ActionFactory(ATProtocolActionFactory)
	, GSMActionContext()
	, GSMActionFactory(GSMActionContext,actionExecutionContextForTest)
	{
	};

	~GSMMModemActionFactoryFixture()
	{
	};

	void SetUp()
	{
		ATProtocolActionFactory.RegisterActionFactory(GSMActionFactory);
		GSMActionContext.RegisterSMSServiceListener(&mock_SMSServiceListener);
	}

	void TearDown()
	{
		GSMActionContext.UnregisterSMSServiceListener(&mock_SMSServiceListener);
	}

	CTimeoutHandlerMock timerHandlerMock;

	CSerialPortHandlerMock serialPortMock;

	ATProtocolEngine::CParameterBundle paramBundleInstance;

	CSerializationEngineMock serializationEngineMock;

	ActionContextMock actionExecutionContextForTest;

	ATProtocolEngine::CATProtocolActionFactory ATProtocolActionFactory;
	
	CSM::IActionFactory& CSM_ActionFactory;

	GSMModemSim800L::CGSMActionContext GSMActionContext;

	GSMModemSim800L::CGSMModemActionFactory GSMActionFactory;

	SMSServiceListenerMock mock_SMSServiceListener;
};


TEST_F( GSMMModemActionFactoryFixture, NotifySMSSendSuccess )
{
	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "NotifySMSSent" );

	ASSERT_TRUE ( 0!= pAction );

	EXPECT_CALL(  mock_SMSServiceListener, NotifySMSSendSuccess() );

	pAction->Execute();
}

TEST_F( GSMMModemActionFactoryFixture, NotifySMSSendFailure )
{
	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "NotifySMSSendFailure" );

	ASSERT_TRUE ( 0!= pAction );

	EXPECT_CALL(  mock_SMSServiceListener, NotifySMSSendFailure() );

	pAction->Execute();
}

TEST_F( GSMMModemActionFactoryFixture, NotifyIncomingSMS )
{
	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "NotifyIncomingSMS" );

	ASSERT_TRUE ( 0!= pAction );

	EXPECT_CALL(  mock_SMSServiceListener, NotifyIncomingSMS( EndsWith("+48123456789"), EndsWith("19.01.2017 19:45"), EndsWith("Test message, for the unit test purposes") ) );

	paramBundleInstance.Store("PHONE_NUMBER", "+48123456789");
	paramBundleInstance.Store("MSG_TIMESTAMP", "19.01.2017 19:45");
	paramBundleInstance.Store("MSG_TEXT", "Test message, for the unit test purposes");

	pAction->Execute();

	
}



