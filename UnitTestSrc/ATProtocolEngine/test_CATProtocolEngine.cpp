#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <CSM/CArgoConfigurator.h>
#include <Runtime/ITimerManager.h>
#include "ATProtocolEngineTestMocks.h"
#include <ATProtocolEngine/CATProtocolEngine.h>
#include <UCL/SystemEnvironment.h>

TEST( CATProtocolEngine, Initialization)
{
	// configurator initialization parameters
	std::string configFile(UCL::SystemEnvironment::ResolveEnvironmentVariable("${UNITTEST_DIR}/ATProtocolEngine/ATProtocolEngine_test.xmi"));
	std::string smName("BasicScenario");
	CSM::CArgoConfigurator configurator(configFile, smName);

	// Create serial port mock
	CSerialPortHandlerMock serialPortMock;

	// Serialization mock
	CSerializationEngineMock serializationEngineMock;

	// Timer manager mock
	TimerMock timerMock;
	
	// class under tests
	ATProtocolEngine::CATProtocolEngine atProtocolEngine(	serializationEngineMock, configurator, serialPortMock, timerMock);

	//  expected calls
	EXPECT_CALL(	timerMock, CreateTimer(&atProtocolEngine)).WillOnce(Return(112));
	EXPECT_CALL(	timerMock, DisposeTimer(112));

	
	atProtocolEngine.Initialize();
	atProtocolEngine.Shutdown();
}

TEST( CATProtocolEngine, BasicSend_Timeout)
{
	// configurator initialization parameters
	std::string configFile(UCL::SystemEnvironment::ResolveEnvironmentVariable("${UNITTEST_DIR}/ATProtocolEngine/ATProtocolEngine_test.xmi"));
	std::string smName("BasicScenario");
	CSM::CArgoConfigurator configurator(configFile, smName);

	// Create serial port mock
	CSerialPortHandlerMock serialPortMock;

	// Serialization mock
	CSerializationEngineMock serializationEngineMock;

	// Timer manager mock
	TimerMock timerMock;
	
	// class under tests
	ATProtocolEngine::CATProtocolEngine atProtocolEngine(	serializationEngineMock, configurator, serialPortMock, timerMock);
	//ATProtocolEngine::IActionExecutionContext& actionContext(atProtocolEngine);
	Runtime::ITimerListener& atProtocolTimoutTrigger(atProtocolEngine);

	//  expected calls
	EXPECT_CALL(	timerMock, CreateTimer(&atProtocolEngine)).WillOnce(Return(112));
	EXPECT_CALL(	serialPortMock, Test_SendCommand(	EndsWith("AT+REG") )).Times(1);
	EXPECT_CALL(  timerMock, SetTimer( 112, 5, 0) ).WillOnce(Return(true));
	EXPECT_CALL(  timerMock, StartTimer( 112) ).WillOnce(Return(true));
	EXPECT_CALL(  timerMock, StopTimer( 112) ).WillOnce(Return(true));	
	EXPECT_CALL(	timerMock, DisposeTimer(112));

	
	atProtocolEngine.Initialize();

	atProtocolEngine.DispatchEvent("E_SEND_DATA");

	atProtocolTimoutTrigger.NotifyTimer(112);
	atProtocolEngine.Shutdown();
}
