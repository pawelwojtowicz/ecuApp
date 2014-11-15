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

TEST( CProcessManager , Initialization )
{
	std::string configFile = UCL::SystemEnvironment::ResolveEnvironmentVariable("${UNITTEST_DIR}/Controller/TestCfg_CSessionManager.xml");
	const Configuration::CConfigNode* pConfig = Configuration::CConfiguration::GetConfiguration(configFile);


}
