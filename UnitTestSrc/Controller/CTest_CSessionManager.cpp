#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ControllerMocks.h"
#include "Controller/CSessionManager.h"

using ::testing::AtLeast;
using ::testing::Return;

using namespace Controller;

TEST( CSessionManager , Initialize )
{
	ControllerTest::TimerManagerMock timerManagerMock;
	CSessionManager manager(timerManagerMock);
	
	EXPECT_CALL(timerManagerMock, CreateTimer(&manager) ).Times(4).WillOnce(Return(2)).WillOnce(Return(3)).WillOnce(Return(4)).WillOnce(Return(5));
	
	manager.Initialize();
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

