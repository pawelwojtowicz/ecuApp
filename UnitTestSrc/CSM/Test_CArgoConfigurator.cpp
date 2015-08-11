#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <CSM/CArgoConfigurator.h>
#include <CSM/ICSMBuilder.h>
#include <UCL/SystemEnvironment.h>

TEST( CArgoConfigurator, OpeningFile_Fails)
{
	std::string configFileChange(UCL::SystemEnvironment::ResolveEnvironmentVariable("${UNITTEST_DIR}/CSM/CSM_testConfig.xmi"));
	CSM::CArgoConfigurator configurator;
	
	ASSERT_FALSE(configurator.InitializeStateMachine(configFileChange,0));
}

TEST( CArgoConfigurator, OpeningFile_Succedes)
{
	std::string configFileChange(UCL::SystemEnvironment::ResolveEnvironmentVariable("${UNITTEST_DIR}/CSM/CSM_testConfig.xmi"));
	CSM::CArgoConfigurator configurator;
	
	
	
	ASSERT_TRUE(configurator.InitializeStateMachine(configFileChange,reinterpret_cast<CSM::ICSMBuilder*>(0x11234)));
}

