#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <CSM/CArgoConfigurator.h>
#include <CSM/ICSMBuilder.h>
#include <UCL/SystemEnvironment.h>
#include "CCSMBuilderMock.h"

TEST( CArgoConfigurator, OpeningFile_Fails)
{
	std::string configFileChange(UCL::SystemEnvironment::ResolveEnvironmentVariable("${UNITTEST_DIR}/CSM/CSM_testConfig.xmi"));
	std::string smName("ConfiguratorTest");
	CSM::CArgoConfigurator configurator;
	
	ASSERT_FALSE(configurator.InitializeStateMachine(configFileChange, smName ,0));
}

TEST( CArgoConfigurator, OpeningFile_Succedes)
{
	std::string configFileChange(UCL::SystemEnvironment::ResolveEnvironmentVariable("${UNITTEST_DIR}/CSM/CSM_testConfig.xmi"));
	std::string smName("ConfiguratorTest");
	CSM::CArgoConfigurator configurator;
	
	
	
	ASSERT_TRUE(configurator.InitializeStateMachine(configFileChange, smName,reinterpret_cast<CSM::ICSMBuilder*>(0x11234)));
}

TEST( CArgoConfigurator, mockTest)
{
	CCSMBuilderMock mockInstance;
	CCSMBuilderIF mockInterface(&mockInstance);
	std::string configFileChange(UCL::SystemEnvironment::ResolveEnvironmentVariable("${UNITTEST_DIR}/CSM/CSM_testConfig.xmi"));
	std::string smName("ConfiguratorTest");

	
	CSM::CArgoConfigurator configurator;
	configurator.InitializeStateMachine(configFileChange,smName ,&mockInterface);
}
