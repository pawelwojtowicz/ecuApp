#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Configuration/CConfiguration.h>
#include <UCL/SystemEnvironment.h>
#include <Runtime/ITimerListener.h>
#include <Controller/CProcessManager.h>
#include <Logger/Logger.h>
#include "ControllerMocks.h"

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::EndsWith;
using ::testing::NotNull;
using ::testing::InSequence;
using ::testing::_;
using namespace Controller;

TEST(CProcessManager, InitialEnvironmentTest)
{
	std::string configFile = UCL::SystemEnvironment::ResolveEnvironmentVariable("${UNITTEST_DIR}/Controller/TestCfg_CProcessManager.xml");
	const Configuration::CConfigNode* pConfig = Configuration::CConfiguration::GetConfiguration(configFile);

	const Configuration::CConfigNode* pProcessManagerConfig = pConfig->GetConfigNode("Processes");
	
	ASSERT_TRUE(pProcessManagerConfig != 0);
	
	ControllerTest::TimerManagerMock timerManagerMock;
	ControllerTest::SessionManagerMock sessionManagerMock;
	ControllerTest::ProcessControlMock processControlMock;
	ControllerTest::ProcessorStatusReporterMock processStatusReporterMock;
	UInt32 testGlobalLoggerMask(0x31);
	
	Controller::CProcessManager processManager(timerManagerMock, sessionManagerMock,processStatusReporterMock, &processControlMock );

	{
		InSequence seq;
		EXPECT_CALL(sessionManagerMock, RegisterSessionListener(NotNull())).Times(1).WillOnce(Return(1) );	
		EXPECT_CALL(timerManagerMock, CreateTimer(&processManager) ).Times(1).WillOnce(Return(1));
		EXPECT_CALL(timerManagerMock, SetTimer(1,5,5 ) );
	
		EXPECT_CALL(processControlMock, AddProcessController(	1, 
																													EndsWith("newTest"),
																													10,
																													testGlobalLoggerMask ) )
																													.Times(1).WillOnce(Return(true) );
																												
		EXPECT_CALL(processControlMock, AddProcessController(	2, 
																													EndsWith("exampleApp"),
																													5,
																													testGlobalLoggerMask ) )
																													.Times(1).WillOnce(Return(true) );

		EXPECT_CALL(processControlMock, AddProcessController(	3, 
																													EndsWith("bukaDziont"),
																													15,
																													testGlobalLoggerMask ) )
																													.Times(1).WillOnce(Return(true) );
																													
		EXPECT_CALL(processControlMock, AddProcessController(	4, 
																													EndsWith("tetraMoja"),
																													20,
																													testGlobalLoggerMask ) )
																													.Times(1).WillOnce(Return(true) );
	}																										
	

	ASSERT_TRUE( processManager.Initialize(pProcessManagerConfig, testGlobalLoggerMask));
	Configuration::CConfiguration::ReleaseConfiguration();
}


class CProcessManager_Test: public ::testing::Test
{
protected:
	CProcessManager_Test()
	: DefaultLoggerMask(0x255)
	, SessionItemID(153)
	, timerManagerMock()
	, sessionManagerMock()
	, processControlMock()
	, processManager(timerManagerMock, sessionManagerMock,processStatusReporterMock ,  &processControlMock)
	{
	}
	

	virtual void SetUp()
	{
		std::string configFile = UCL::SystemEnvironment::ResolveEnvironmentVariable("${UNITTEST_DIR}/Controller/TestCfg_CProcessManager.xml");
		const Configuration::CConfigNode* pConfig = Configuration::CConfiguration::GetConfiguration(configFile);

		const Configuration::CConfigNode* pProcessManagerConfig = pConfig->GetConfigNode("Processes");
	
		ASSERT_TRUE(pProcessManagerConfig != 0);
		EXPECT_CALL(sessionManagerMock, RegisterSessionListener(NotNull())).Times(1).WillOnce(Return(SessionItemID) );
		EXPECT_CALL(timerManagerMock, CreateTimer(&processManager) ).Times(1).WillOnce(Return(ProcessMonitorTimerID));
		EXPECT_CALL(timerManagerMock, SetTimer(ProcessMonitorTimerID,5,5 ) );
	
	
		EXPECT_CALL(processControlMock, AddProcessController(	1, 
																													EndsWith("newTest"),
																													10,
																													DefaultLoggerMask ) )
																													.Times(1).WillOnce(Return(true) );
																												
		EXPECT_CALL(processControlMock, AddProcessController(	2, 
																													EndsWith("exampleApp"),
																													5,
																													DefaultLoggerMask ) )
																													.Times(1).WillOnce(Return(true) );

		EXPECT_CALL(processControlMock, AddProcessController(	3, 
																													EndsWith("bukaDziont"),
																													15,
																													DefaultLoggerMask ) )
																													.Times(1).WillOnce(Return(true) );

		EXPECT_CALL(processControlMock, AddProcessController(	4, 
																													EndsWith("tetraMoja"),
																													20,
																													DefaultLoggerMask ) )
																													.Times(1).WillOnce(Return(true) );

		ASSERT_TRUE(processManager.Initialize(pProcessManagerConfig , DefaultLoggerMask) );
	}
	
	virtual void TearDown()
	{
		processManager.Shutdown();
		
		Configuration::CConfiguration::ReleaseConfiguration();
	}
	
	UInt32 DefaultLoggerMask;
	
	Int32 SessionItemID;
	
	Int32 ProcessMonitorTimerID;
	
	ControllerTest::ProcessorStatusReporterMock processStatusReporterMock;

	ControllerTest::TimerManagerMock timerManagerMock;

	ControllerTest::SessionManagerMock sessionManagerMock;
	
	ControllerTest::ProcessControlMock processControlMock;
	
	Controller::CProcessManager processManager;
};

TEST_F( CProcessManager_Test , ShortNameList4Logger )
{
	tStringVector runtimeShortnameList;
	processManager.GetRuntimeUnitShortnameList(runtimeShortnameList);
	
	EXPECT_EQ(runtimeShortnameList.size(), 5 );
	EXPECT_EQ(runtimeShortnameList[1], std::string("NVP") );
	EXPECT_EQ(runtimeShortnameList[2], std::string("TST") );
	EXPECT_EQ(runtimeShortnameList[3], std::string("BKD") );
	EXPECT_EQ(runtimeShortnameList[4], std::string("TMA") );
}


TEST_F( CProcessManager_Test , NotifySessionState_Init1 )
{
	ISessionStateListener& sessionStateListener(processManager);
	
	EXPECT_CALL(processControlMock, StartProcess(1)).Times(1);

	ASSERT_TRUE(sessionStateListener.NotifySessionState(eSessionState_Init1));
}

TEST_F( CProcessManager_Test , NotifySessionState_Init2 )
{
	ISessionStateListener& sessionStateListener(processManager);
	
	EXPECT_CALL(processControlMock, StartProcess(2)).Times(1);
	EXPECT_CALL(processControlMock, StartProcess(3)).Times(1);
	EXPECT_CALL(processControlMock, StartProcess(4)).Times(1);

	ASSERT_TRUE(sessionStateListener.NotifySessionState(eSessionState_Init2));
}

TEST_F( CProcessManager_Test , NotifySessionState_Init3 )
{
	ISessionStateListener& sessionStateListener(processManager);
	
	EXPECT_CALL(processControlMock, StartProcess(1)).Times(0);

	ASSERT_TRUE(!sessionStateListener.NotifySessionState(eSessionState_Init3));
}

TEST_F(CProcessManager_Test , HeartbeatOnTheProcessMissing )
{
	Int32 timestamp(10000);
	Runtime::ITimerListener& timerListener(processManager);
	EXPECT_CALL(timerManagerMock,GetCurrentTime()).Times(7).WillOnce(Return(timestamp)).WillOnce(Return(timestamp)).WillOnce(Return(timestamp)).WillOnce(Return(timestamp)).WillOnce(Return(timestamp+6000)).WillOnce(Return(timestamp+11000)).WillOnce(Return(timestamp+16000));
	EXPECT_CALL(sessionManagerMock, ReportItemState( SessionItemID, true )).Times(4);

	EXPECT_CALL(processControlMock, TerminateProcess(2)).Times(1);
	
	processManager.NotifyUnitHeartbeat(1,Controller::eStatus_Busy);
	processManager.NotifyUnitHeartbeat(2,Controller::eStatus_Busy);
	processManager.NotifyUnitHeartbeat(3,Controller::eStatus_Busy);
	processManager.NotifyUnitHeartbeat(4,Controller::eStatus_Busy);

	
	timerListener.NotifyTimer(ProcessMonitorTimerID);
	timerListener.NotifyTimer(ProcessMonitorTimerID);
	timerListener.NotifyTimer(ProcessMonitorTimerID);
}


TEST_F(CProcessManager_Test , ProcessBusyIddle )
{
	Int32 timestamp(10000);
	
	Runtime::ITimerListener& timerListener(processManager);
	EXPECT_CALL(timerManagerMock,GetCurrentTime()).Times(8).WillRepeatedly(Return(timestamp));
	EXPECT_CALL(processControlMock, TerminateProcess(_)).Times(0);
	EXPECT_CALL(sessionManagerMock, ReportItemState( SessionItemID, true )).Times(7);
	EXPECT_CALL(sessionManagerMock, ReportItemState( SessionItemID, false )).Times(1);
	
	processManager.NotifyUnitHeartbeat(1,Controller::eStatus_Busy);
	processManager.NotifyUnitHeartbeat(2,Controller::eStatus_Busy);
	processManager.NotifyUnitHeartbeat(3,Controller::eStatus_Busy);
	processManager.NotifyUnitHeartbeat(4,Controller::eStatus_Busy);
	processManager.NotifyUnitHeartbeat(1,Controller::eStatus_Iddle);
	processManager.NotifyUnitHeartbeat(2,Controller::eStatus_Iddle);
	processManager.NotifyUnitHeartbeat(3,Controller::eStatus_Iddle);
	processManager.NotifyUnitHeartbeat(4,Controller::eStatus_Iddle);
}
