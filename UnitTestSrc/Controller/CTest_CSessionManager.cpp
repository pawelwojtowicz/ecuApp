#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Configuration/CConfiguration.h>
#include <UCL/SystemEnvironment.h>
#include "ControllerMocks.h"
#include "Controller/CSessionManager.h"

using ::testing::AtLeast;
using ::testing::Return;

using namespace Controller;

TEST( CSessionManager , Initialize )
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
	EXPECT_CALL(stateListenerMock, NotifySessionState(Controller::eSessionState_Iddle)).Times(1).WillOnce(Return(false));

	
	Controller::ISessionManager& iSessionManager(manager);
	iSessionManager.RegisterSessionListener(&stateListenerMock);
	manager.Initialize(pSessionMngmtCfg);
	
	manager.ShutdownRequest();
}

TEST(CSessionManager , RegisteringItems)
{
	//instantiate mocks
	ControllerTest::TimerManagerMock timerManagerMock;
	ControllerTest::SessionStateListenerMock stateListenerMock1;
	ControllerTest::SessionStateListenerMock stateListenerMock2;
	ControllerTest::SessionStateListenerMock stateListenerMock3;
	
	//instantiate the test subject
	CSessionManager manager(timerManagerMock);
	Controller::ISessionManager& iSessionManager(manager);
	
	EXPECT_EQ(1, iSessionManager.RegisterSessionListener(&stateListenerMock1));
	EXPECT_EQ(2, iSessionManager.RegisterSessionListener(&stateListenerMock2));
	EXPECT_EQ(3, iSessionManager.RegisterSessionListener(&stateListenerMock3));
}

TEST(CSessionManager , BasicNotifierTest)
{
	//instantiate mocks
	ControllerTest::TimerManagerMock timerManagerMock;
	ControllerTest::SessionStateListenerMock stateListenerMock1;
	ControllerTest::SessionStateListenerMock stateListenerMock2;
	ControllerTest::SessionStateListenerMock stateListenerMock3;
	
	//instantiate the test subject
	CSessionManager manager(timerManagerMock);
	Controller::ISessionManager& iSessionManager(manager);
	
	iSessionManager.RegisterSessionListener(&stateListenerMock1);
	iSessionManager.RegisterSessionListener(&stateListenerMock2);
	iSessionManager.RegisterSessionListener(&stateListenerMock3);
	
	EXPECT_CALL(stateListenerMock1, NotifySessionState(Controller::eSessionState_Iddle)).Times(1).WillOnce(Return(true));
	EXPECT_CALL(stateListenerMock2, NotifySessionState(Controller::eSessionState_Iddle)).Times(1).WillOnce(Return(true));
	EXPECT_CALL(stateListenerMock3, NotifySessionState(Controller::eSessionState_Iddle)).Times(1).WillOnce(Return(true));
	
	manager.NotifySessionStateListeners(Controller::eSessionState_Iddle);
	
	EXPECT_EQ(true, manager.IsBusy());
}

TEST(CSessionManager , BusyCheckerTest_2Busy1Iddle)
{
	//instantiate mocks
	ControllerTest::TimerManagerMock timerManagerMock;
	ControllerTest::SessionStateListenerMock stateListenerMock1;
	ControllerTest::SessionStateListenerMock stateListenerMock2;
	ControllerTest::SessionStateListenerMock stateListenerMock3;
	
	//instantiate the test subject
	CSessionManager manager(timerManagerMock);
	Controller::ISessionManager& iSessionManager(manager);
	
	iSessionManager.RegisterSessionListener(&stateListenerMock1);
	iSessionManager.RegisterSessionListener(&stateListenerMock2);
	iSessionManager.RegisterSessionListener(&stateListenerMock3);
	
	EXPECT_CALL(stateListenerMock1, NotifySessionState(Controller::eSessionState_Iddle)).Times(1).WillOnce(Return(true));
	EXPECT_CALL(stateListenerMock2, NotifySessionState(Controller::eSessionState_Iddle)).Times(1).WillOnce(Return(false));
	EXPECT_CALL(stateListenerMock3, NotifySessionState(Controller::eSessionState_Iddle)).Times(1).WillOnce(Return(true));
	
	manager.NotifySessionStateListeners(Controller::eSessionState_Iddle);
	
	EXPECT_EQ(true, manager.IsBusy());
}

TEST(CSessionManager , BusyCheckerTest_1Busy2Iddle)
{
	//instantiate mocks
	ControllerTest::TimerManagerMock timerManagerMock;
	ControllerTest::SessionStateListenerMock stateListenerMock1;
	ControllerTest::SessionStateListenerMock stateListenerMock2;
	ControllerTest::SessionStateListenerMock stateListenerMock3;
	
	//instantiate the test subject
	CSessionManager manager(timerManagerMock);
	Controller::ISessionManager& iSessionManager(manager);
	
	iSessionManager.RegisterSessionListener(&stateListenerMock1);
	iSessionManager.RegisterSessionListener(&stateListenerMock2);
	iSessionManager.RegisterSessionListener(&stateListenerMock3);
	
	EXPECT_CALL(stateListenerMock1, NotifySessionState(Controller::eSessionState_Iddle)).Times(1).WillOnce(Return(false));
	EXPECT_CALL(stateListenerMock2, NotifySessionState(Controller::eSessionState_Iddle)).Times(1).WillOnce(Return(false));
	EXPECT_CALL(stateListenerMock3, NotifySessionState(Controller::eSessionState_Iddle)).Times(1).WillOnce(Return(true));
	
	manager.NotifySessionStateListeners(Controller::eSessionState_Iddle);
	
	EXPECT_EQ(true, manager.IsBusy());
}

TEST(CSessionManager , BusyCheckerTest_0Busy3Iddle)
{
	//instantiate mocks
	ControllerTest::TimerManagerMock timerManagerMock;
	ControllerTest::SessionStateListenerMock stateListenerMock1;
	ControllerTest::SessionStateListenerMock stateListenerMock2;
	ControllerTest::SessionStateListenerMock stateListenerMock3;
	
	//instantiate the test subject
	CSessionManager manager(timerManagerMock);
	Controller::ISessionManager& iSessionManager(manager);
	
	iSessionManager.RegisterSessionListener(&stateListenerMock1);
	iSessionManager.RegisterSessionListener(&stateListenerMock2);
	iSessionManager.RegisterSessionListener(&stateListenerMock3);
	
	EXPECT_CALL(stateListenerMock1, NotifySessionState(Controller::eSessionState_Iddle)).Times(1).WillOnce(Return(false));
	EXPECT_CALL(stateListenerMock2, NotifySessionState(Controller::eSessionState_Iddle)).Times(1).WillOnce(Return(false));
	EXPECT_CALL(stateListenerMock3, NotifySessionState(Controller::eSessionState_Iddle)).Times(1).WillOnce(Return(false));
	
	manager.NotifySessionStateListeners(Controller::eSessionState_Iddle);
	
	EXPECT_EQ(false, manager.IsBusy());
}

