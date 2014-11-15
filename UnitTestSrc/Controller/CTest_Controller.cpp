#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <UCL/SystemEnvironment.h>
#include "Controller/CProcessInfo.h"
#include "Configuration/CConfiguration.h"

using ::testing::AtLeast;
using ::testing::Return;

using namespace Controller;


TEST( CProcessInfo ,ConfigParsing )
{
	std::string configFile = UCL::SystemEnvironment::ResolveEnvironmentVariable("${UNITTEST_DIR}/Controller/TestCfg_CProcessInfo.xml");
	const Configuration::CConfigNode* pConfig = Configuration::CConfiguration::GetConfiguration(configFile);
	
	EXPECT_EQ( 0 != pConfig , true );
	
	const Configuration::CConfigNode* pProcessMgrConfig = pConfig->GetConfigNode("ProcessManager");
	EXPECT_EQ( 0 != pProcessMgrConfig, true );
	
	const Configuration::CConfigNode* pProcessConfig = pProcessMgrConfig->GetFirstSubnode();
	
	EXPECT_EQ( 0 != pProcessConfig, true );
	
	UInt32 processID(110);
	UInt32 defaultDebugZones(124);
	
	CProcessInfo* pProcessInfo = new CProcessInfo(processID, defaultDebugZones, pProcessConfig);
	
	EXPECT_EQ( pProcessInfo->GetProcessID(), processID );
		
	EXPECT_EQ( pProcessInfo->GetDebugZoneSettings(), 124U );
	
	EXPECT_EQ( pProcessInfo->GetShortName(), "TST");
	
	EXPECT_EQ( pProcessInfo->GetStartupGroup(), 6U );
	
	EXPECT_EQ( pProcessInfo->GetShutdownGroup(), 3U );
	
	EXPECT_EQ( pProcessInfo->GetHeartbeatTimeout() , 5U );
	
	Configuration::CConfiguration::ReleaseConfiguration();

}

