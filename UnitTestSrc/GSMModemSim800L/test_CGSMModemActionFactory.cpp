#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <GSMModemSim800L/CGSMModemActionFactory.h>
#include <GSMModemSim800L/CGSMActionContext.h>
#include <ATProtocolEngine/CParameterBundle.h>
#include "../ATProtocolEngine/ATProtocolEngineTestMocks.h"

#include <ATProtocolEngine/CATProtocolActionFactory.h>
#include "GSMActionContextMocks.h"
#include <CSM/IAction.h>
#include <GSMModemSim800L/GSMModemSim800LConst.h>

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
		GSMActionContext.RegisterModemListener(&mock_ModemListener);
		GSMActionContext.RegisterVoiceServiceListener(&mock_VoiceServiceListener);
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

	ModemListenerMock mock_ModemListener;

	VoiceServiceListenerMock mock_VoiceServiceListener;
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

	paramBundleInstance.Store(GSMModemSim800L::sc_CMGL_msgOrgNo, "+48123456789");
	paramBundleInstance.Store(GSMModemSim800L::sc_CMGL_msgTimeStamp, "19.01.2017 19:45");
	paramBundleInstance.Store(GSMModemSim800L::sc_CMGL_msgContent, "Test message, for the unit test purposes");

	pAction->Execute();

	
}

TEST_F( GSMMModemActionFactoryFixture, NotifyModemManufacturerReceived )
{
	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "NotifyModemManufacturerReceived" );

	ASSERT_TRUE ( 0!= pAction );

	EXPECT_CALL(  mock_ModemListener, NotifyModemManufacturerReceived( EndsWith("WOJTECH BEJBI") ) );

	paramBundleInstance.Store(GSMModemSim800L::sc_RAW_DATA, "WOJTECH BEJBI");

	pAction->Execute();

	
}
TEST_F( GSMMModemActionFactoryFixture, NotifyModemTypeReceived )
{
	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "NotifyModemTypeReceived" );

	ASSERT_TRUE ( 0!= pAction );

	EXPECT_CALL(  mock_ModemListener, NotifyModemTypeReceived( EndsWith("modemType") ) );

	paramBundleInstance.Store(GSMModemSim800L::sc_RAW_DATA, "modemType");

	pAction->Execute();

	
}

TEST_F( GSMMModemActionFactoryFixture, NotifyModemIMEIReceived )
{
	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "NotifyModemIMEIReceived" );

	ASSERT_TRUE ( 0!= pAction );

	EXPECT_CALL(  mock_ModemListener, NotifyModemIMEIReceived( EndsWith("IMEI") ) );

	paramBundleInstance.Store(GSMModemSim800L::sc_RAW_DATA, "IMEI");

	pAction->Execute();
}

TEST_F( GSMMModemActionFactoryFixture, NotifyRegStateReceived )
{
	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "NotifyRegStateReceived" );

	ASSERT_TRUE ( 0!= pAction );

	EXPECT_CALL(  mock_ModemListener, NotifyRegistrationStateReceived( GSMDaemon::gsmConnecting ) );

	paramBundleInstance.Store(GSMModemSim800L::sc_CREG_regStatus, "2");

	pAction->Execute();
}

TEST_F( GSMMModemActionFactoryFixture, NotifySignalStrengthReceived )
{
	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "NotifySignalStrengthReceived" );

	ASSERT_TRUE ( 0!= pAction );

	EXPECT_CALL(  mock_ModemListener, NotifySignalStrengthReceived( 24 ) );

	paramBundleInstance.Store(GSMModemSim800L::sc_CSQ_rssi, "24");

	pAction->Execute();
}

TEST_F( GSMMModemActionFactoryFixture, NotifyProviderNameReceived )
{
	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "NotifyProviderNameReceived" );

	ASSERT_TRUE ( 0!= pAction );

	EXPECT_CALL(  mock_ModemListener, NotifyGSMProviderNameReceived( "PLUS GSM" ) );

	paramBundleInstance.Store(GSMModemSim800L::sc_COPS_operatorName, "PLUS GSM");

	pAction->Execute();
}

TEST_F( GSMMModemActionFactoryFixture, NotifyNumberBusy )
{
	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "NotifyNumberBusy" );

	ASSERT_TRUE ( 0!= pAction );

	EXPECT_CALL(  mock_VoiceServiceListener, NotifyBusy( ) );

	pAction->Execute();
}

TEST_F( GSMMModemActionFactoryFixture, NotifyConnectionEstablished )
{
	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "NotifyConnectionEstablished" );

	ASSERT_TRUE ( 0!= pAction );

	EXPECT_CALL(  mock_VoiceServiceListener, NotifyConnectionEstablished() );

	pAction->Execute();
}

TEST_F( GSMMModemActionFactoryFixture, NotifyConnectionTerminated )
{
	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "NotifyConnectionTerminated" );

	ASSERT_TRUE ( 0!= pAction );

	EXPECT_CALL(  mock_VoiceServiceListener, NotifyConnectionTerminated() );

	pAction->Execute();
}

TEST_F( GSMMModemActionFactoryFixture, NotifyIncomingCall )
{
	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "NotifyIncomingCall" );

	ASSERT_TRUE ( 0!= pAction );

	EXPECT_CALL(  mock_VoiceServiceListener, NotifyIncomingCall() );

	pAction->Execute();
}

TEST_F( GSMMModemActionFactoryFixture, NotifyNumberCalling )
{
	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "NotifyNumberCalling" );

	ASSERT_TRUE ( 0!= pAction );

	EXPECT_CALL(  mock_VoiceServiceListener, NotifyIncomingCallNumber( EndsWith("+48696083896")) );

	paramBundleInstance.Store(GSMModemSim800L::sc_CLIP_number, "+48696083896");

	pAction->Execute();
}

TEST_F( GSMMModemActionFactoryFixture, NotifyDTMFCode )
{
	CSM::IAction* pAction = CSM_ActionFactory.GetAction( "NotifyDTMFCode" );

	ASSERT_TRUE ( 0!= pAction );

	EXPECT_CALL(  mock_VoiceServiceListener, NotifyDTMFCode( EndsWith("#")) );

	paramBundleInstance.Store(GSMModemSim800L::sc_DTMF_code, "#");

	pAction->Execute();
}

