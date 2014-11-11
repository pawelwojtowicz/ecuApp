#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ControllerMocks.h"
#include "Controller/CSessionManager.h"

using ::testing::AtLeast;
using ::testing::Return;

using namespace Controller;

TEST( CSessionManager , AddingListeners )
{
	ControllerTest::TimerManagerMock timerManagerMock;
	CSessionManager manager(timerManagerMock);
	
	EXPECT_CALL(timerManagerMock, CreateTimer(&manager) ).Times(4).WillOnce(Return(2)).WillOnce(Return(3)).WillOnce(Return(4)).WillOnce(Return(5));
	
	manager.Initialize();
}

