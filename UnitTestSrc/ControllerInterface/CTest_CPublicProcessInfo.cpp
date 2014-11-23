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
