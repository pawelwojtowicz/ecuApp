#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <CSM/CStateMachine.h>

TEST( CStateMachine, BasicTest)
{
	CSM::CStateMachine stateMachine;
	
	EXPECT_FALSE(stateMachine.DispatchEvent("EXAMPLE"));
}
