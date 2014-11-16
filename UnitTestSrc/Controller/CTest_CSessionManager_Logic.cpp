#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Configuration/CConfiguration.h>
#include <UCL/SystemEnvironment.h>
#include "ControllerMocks.h"
#include <Controller/CSessionManager.h>
#include <Runtime/ITimerListener.h>

using ::testing::AtLeast;
using ::testing::Return;

using namespace Controller;

TEST( CSessionManager_Logic , BasicSequence_AllIdle )
{
	ControllerTest::TimerManagerMock timerManagerMock;
	ControllerTest::SessionStateListenerMock stateListenerMock;

	CSessionManager manager(timerManagerMock);
	
	EXPECT_CALL(timerManagerMock, CreateTimer(&manager) ).Times(1).WillOnce(Return(1));
	EXPECT_CALL(timerManagerMock, StopTimer(1) ).Times(6);
	
	std::string configFile = UCL::SystemEnvironment::ResolveEnvironmentVariable("${UNITTEST_DIR}/Controller/TestCfg_CSessionManager.xml");
	const Configuration::CConfigNode* pConfig = Configuration::CConfiguration::GetConfiguration(configFile);
	
	const Configuration::CConfigNode* pSessionMngmtCfg = pConfig->GetConfigNode("SessionManagment");
	
	EXPECT_CALL(stateListenerMock, NotifySessionState(Controller::eSessionState_Init1)).Times(1).WillOnce(Return(false));
	EXPECT_CALL(stateListenerMock, NotifySessionState(Controller::eSessionState_Init2)).Times(1).WillOnce(Return(false));
	EXPECT_CALL(stateListenerMock, NotifySessionState(Controller::eSessionState_Init3)).Times(1).WillOnce(Return(false));
	EXPECT_CALL(stateListenerMock, NotifySessionState(Controller::eSessionState_Running)).Times(1).WillOnce(Return(false));
	EXPECT_CALL(stateListenerMock, NotifySessionState(Controller::eSessionState_Shutdown)).Times(1).WillOnce(Return(false));
	EXPECT_CALL(stateListenerMock, NotifySessionState(Controller::eSessionState_PowerOff)).Times(1).WillOnce(Return(false));

	
	Controller::ISessionManager& iSessionManager(manager);
	iSessionManager.RegisterSessionListener(&stateListenerMock);
	manager.Initialize(pSessionMngmtCfg);
		
	manager.ShutdownRequest();
}


TEST( CSessionManager_Logic , StepByStep )
{
	ControllerTest::TimerManagerMock timerManagerMock;
	ControllerTest::SessionStateListenerMock stateListenerMock;

	CSessionManager manager(timerManagerMock);
	std::string configFile = UCL::SystemEnvironment::ResolveEnvironmentVariable("${UNITTEST_DIR}/Controller/TestCfg_CSessionManager.xml");
	
	const Configuration::CConfigNode* pConfig = Configuration::CConfiguration::GetConfiguration(configFile);
	const Configuration::CConfigNode* pSessionMngmtCfg = pConfig->GetConfigNode("SessionManagment");

	Controller::ISessionManager& iSessionManager(manager);
	//Runtime::ITimerListener& timerListener(manager);
	iSessionManager.RegisterSessionListener(&stateListenerMock);

	EXPECT_CALL(timerManagerMock, CreateTimer(&manager) ).Times(1).WillOnce(Return(1));
	EXPECT_CALL(timerManagerMock, StopTimer(1) ).Times(1);
	EXPECT_CALL(timerManagerMock, SetTimer(1,1,0) ).Times(1);
	EXPECT_CALL(timerManagerMock, StartTimer(1) ).Times(1);

	EXPECT_CALL(stateListenerMock, NotifySessionState(Controller::eSessionState_Init1)).Times(1).WillOnce(Return(true));

	manager.Initialize(pSessionMngmtCfg);

	EXPECT_CALL(timerManagerMock, StopTimer(1) ).Times(1);
	EXPECT_CALL(stateListenerMock, NotifySessionState(Controller::eSessionState_Init2)).Times(1).WillOnce(Return(true));
	EXPECT_CALL(timerManagerMock, SetTimer(1,2,0) ).Times(1);
	EXPECT_CALL(timerManagerMock, StartTimer(1) ).Times(1);
	
	iSessionManager.ReportItemState(1,false);
	
	EXPECT_CALL(timerManagerMock, StopTimer(1) ).Times(1);
	EXPECT_CALL(stateListenerMock, NotifySessionState(Controller::eSessionState_Init3)).Times(1).WillOnce(Return(true));
	EXPECT_CALL(timerManagerMock, SetTimer(1,3,0) ).Times(1);
	EXPECT_CALL(timerManagerMock, StartTimer(1) ).Times(1);
	
	iSessionManager.ReportItemState(1,false);
	
	EXPECT_CALL(timerManagerMock, StopTimer(1) ).Times(1);
	EXPECT_CALL(stateListenerMock, NotifySessionState(Controller::eSessionState_Running)).Times(1).WillOnce(Return(false));
	
	iSessionManager.ReportItemState(1,false);
	iSessionManager.ReportItemState(1,true);

	EXPECT_CALL(stateListenerMock, NotifySessionState(Controller::eSessionState_PendingShutdown)).Times(1).WillOnce(Return(true));
	EXPECT_CALL(timerManagerMock, StopTimer(1) ).Times(1);
	EXPECT_CALL(timerManagerMock, SetTimer(1,4,0) ).Times(1);
	EXPECT_CALL(timerManagerMock, StartTimer(1) ).Times(1);
	
	manager.ShutdownRequest();

	EXPECT_CALL(stateListenerMock, NotifySessionState(Controller::eSessionState_Shutdown)).Times(1).WillOnce(Return(true));
	EXPECT_CALL(timerManagerMock, StopTimer(1) ).Times(1);
	EXPECT_CALL(timerManagerMock, SetTimer(1,5,0) ).Times(1);
	EXPECT_CALL(timerManagerMock, StartTimer(1) ).Times(1);
	
	iSessionManager.ReportItemState(1,false);
	
	EXPECT_CALL(stateListenerMock, NotifySessionState(Controller::eSessionState_PowerOff)).Times(1).WillOnce(Return(true));
	EXPECT_CALL(timerManagerMock, StopTimer(1) ).Times(1);
	
	iSessionManager.ReportItemState(1,false);


}

TEST( CSessionManager_Logic , TimeoutOnEachStep )
{
	ControllerTest::TimerManagerMock timerManagerMock;
	ControllerTest::SessionStateListenerMock stateListenerMock;

	CSessionManager manager(timerManagerMock);
	std::string configFile = UCL::SystemEnvironment::ResolveEnvironmentVariable("${UNITTEST_DIR}/Controller/TestCfg_CSessionManager.xml");
	
	const Configuration::CConfigNode* pConfig = Configuration::CConfiguration::GetConfiguration(configFile);
	const Configuration::CConfigNode* pSessionMngmtCfg = pConfig->GetConfigNode("SessionManagment");

	Controller::ISessionManager& iSessionManager(manager);
	Runtime::ITimerListener& timerListener(manager);
	iSessionManager.RegisterSessionListener(&stateListenerMock);

	EXPECT_CALL(timerManagerMock, CreateTimer(&manager) ).Times(1).WillOnce(Return(1));
	EXPECT_CALL(timerManagerMock, StopTimer(1) ).Times(1);
	EXPECT_CALL(timerManagerMock, SetTimer(1,1,0) ).Times(1);
	EXPECT_CALL(timerManagerMock, StartTimer(1) ).Times(1);

	EXPECT_CALL(stateListenerMock, NotifySessionState(Controller::eSessionState_Init1)).Times(1).WillOnce(Return(true));

	manager.Initialize(pSessionMngmtCfg);

	EXPECT_CALL(timerManagerMock, StopTimer(1) ).Times(1);
	EXPECT_CALL(stateListenerMock, NotifySessionState(Controller::eSessionState_Init2)).Times(1).WillOnce(Return(true));
	EXPECT_CALL(timerManagerMock, SetTimer(1,2,0) ).Times(1);
	EXPECT_CALL(timerManagerMock, StartTimer(1) ).Times(1);
	
	timerListener.NotifyTimer(1);
	
	EXPECT_CALL(timerManagerMock, StopTimer(1) ).Times(1);
	EXPECT_CALL(stateListenerMock, NotifySessionState(Controller::eSessionState_Init3)).Times(1).WillOnce(Return(true));
	EXPECT_CALL(timerManagerMock, SetTimer(1,3,0) ).Times(1);
	EXPECT_CALL(timerManagerMock, StartTimer(1) ).Times(1);
	
	timerListener.NotifyTimer(1);
	
	EXPECT_CALL(timerManagerMock, StopTimer(1) ).Times(1);
	EXPECT_CALL(stateListenerMock, NotifySessionState(Controller::eSessionState_Running)).Times(1).WillOnce(Return(false));
	
	iSessionManager.ReportItemState(1,false);
	iSessionManager.ReportItemState(1,true);

	EXPECT_CALL(stateListenerMock, NotifySessionState(Controller::eSessionState_PendingShutdown)).Times(1).WillOnce(Return(true));
	EXPECT_CALL(timerManagerMock, StopTimer(1) ).Times(1);
	EXPECT_CALL(timerManagerMock, SetTimer(1,4,0) ).Times(1);
	EXPECT_CALL(timerManagerMock, StartTimer(1) ).Times(1);
	
	manager.ShutdownRequest();

	EXPECT_CALL(stateListenerMock, NotifySessionState(Controller::eSessionState_Shutdown)).Times(1).WillOnce(Return(true));
	EXPECT_CALL(timerManagerMock, StopTimer(1) ).Times(1);
	EXPECT_CALL(timerManagerMock, SetTimer(1,5,0) ).Times(1);
	EXPECT_CALL(timerManagerMock, StartTimer(1) ).Times(1);
	
	timerListener.NotifyTimer(1);
	
	EXPECT_CALL(stateListenerMock, NotifySessionState(Controller::eSessionState_PowerOff)).Times(1).WillOnce(Return(true));
	EXPECT_CALL(timerManagerMock, StopTimer(1) ).Times(1);
	
	timerListener.NotifyTimer(1);
	
	Configuration::CConfiguration::ReleaseConfiguration();
}
