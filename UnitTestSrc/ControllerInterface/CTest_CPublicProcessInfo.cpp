#include <gtest/gtest.h>
#include <ControllerInterface/CPublicProcessInfo.h>

TEST( CPublicProcessInfo, RequiredStorageCalculation)
{
	Controller::CPublicProcessInfo publicInfo;
	
	size_t structureSize(0);
	
	structureSize += sizeof( UInt32 );
	structureSize += sizeof(UInt8) + sizeof(std::string::value_type)* 20; // process name
	structureSize += sizeof(UInt8) + sizeof(std::string::value_type)* 20; // version info 
	structureSize += sizeof(UInt8); //tProcessStatus - will be casted to UInt8

	structureSize *= PROCESS_COUNT; // we assume this many of those
	
	structureSize += sizeof(UInt32); // for element count;
	
	UCL::CSerializable& rPublicInfoAsCSerializable(publicInfo);
	
	EXPECT_EQ(structureSize , rPublicInfoAsCSerializable.GetStorageSize() );
}

TEST( CPublicProcessInfo, SerializeDeserialize)
{
	Controller::CPublicProcessInfo publicInfo_IN;
	UCL::CSerializable& rPublicInfoAsCSerializable(publicInfo_IN);

	// allocate the carrier buffer
	Int8* pCarrierBuffer = new Int8[rPublicInfoAsCSerializable.GetStorageSize()];
	
	{
		Controller::CPublicProcessInfo::tPublicProcessInfoList& processInfo = publicInfo_IN.GetProcessInfo(); 
	
		{
			Controller::CPublicProcessInfo::ProcessInfoStruct infoStruct;
			infoStruct.ProcessID = 123;
			infoStruct.ProcessName = std::string("testSomething");
			infoStruct.VersionInformation = std::string("AgainThe test");
			infoStruct.UnitState = Controller::eStatus_Busy;
		
			processInfo.push_back(infoStruct);
		}
		
		{
			Controller::CPublicProcessInfo::ProcessInfoStruct infoStruct;
			infoStruct.ProcessID = 121;
			infoStruct.ProcessName = std::string("wertgs");
			infoStruct.VersionInformation = std::string("OtherOne");
			infoStruct.UnitState = Controller::eStatus_Iddle;
		
			processInfo.push_back(infoStruct);
		}
		
		ASSERT_TRUE(rPublicInfoAsCSerializable.Serialize(pCarrierBuffer, rPublicInfoAsCSerializable.GetStorageSize()));
	}
	
	Controller::CPublicProcessInfo publicInfo_OUT;
	{
		UCL::CSerializable& rPublicInfoOUTAsCSerializable(publicInfo_OUT);

		ASSERT_TRUE(rPublicInfoOUTAsCSerializable.Deserialize(pCarrierBuffer, rPublicInfoOUTAsCSerializable.GetStorageSize()));
		
		Controller::CPublicProcessInfo::tPublicProcessInfoList& processInfoIN = publicInfo_IN.GetProcessInfo();
		Controller::CPublicProcessInfo::tPublicProcessInfoList& processInfoOUT = publicInfo_OUT.GetProcessInfo();
		
		EXPECT_EQ( processInfoIN.size(), processInfoOUT.size() );
		
		EXPECT_EQ( processInfoIN[0].ProcessID, processInfoOUT[0].ProcessID );
		EXPECT_EQ( processInfoIN[0].ProcessName, processInfoOUT[0].ProcessName );
		EXPECT_EQ( processInfoIN[0].VersionInformation, processInfoOUT[0].VersionInformation );
		EXPECT_EQ( processInfoIN[0].UnitState, processInfoOUT[0].UnitState );

		EXPECT_EQ( processInfoIN[1].ProcessID, processInfoOUT[1].ProcessID );
		EXPECT_EQ( processInfoIN[1].ProcessName, processInfoOUT[1].ProcessName );
		EXPECT_EQ( processInfoIN[1].VersionInformation, processInfoOUT[1].VersionInformation );
		EXPECT_EQ( processInfoIN[1].UnitState, processInfoOUT[1].UnitState );

	}
	
}
