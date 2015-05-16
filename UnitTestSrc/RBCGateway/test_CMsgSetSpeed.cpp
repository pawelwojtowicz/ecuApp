#include <gtest/gtest.h>
#include <RBCGateway/RBCTypes.h>
#include <RBCGateway/CMsgSetSpeed.h>
#define TEST_BUFFER_SIZE 100
TEST( CMsgSetSpeed,BasicSize )
{	
	RBCGateway::CMsgSetSpeed msg;
	
	msg.SetAddress(RBCGateway::moduleStepping_1);
	
	Int8 testBuffer[TEST_BUFFER_SIZE];
	
	size_t outputMsgSize( msg.Serialize(testBuffer,TEST_BUFFER_SIZE) );


	EXPECT_EQ( outputMsgSize , 36 );
	
}

TEST( CMsgSetSpeed,BasicSize_8Motors )
{	
	RBCGateway::CMsgSetSpeed msg(8);
	
	msg.SetAddress(RBCGateway::moduleStepping_1);
	
	Int8 testBuffer[TEST_BUFFER_SIZE];
	
	size_t outputMsgSize( msg.Serialize(testBuffer,TEST_BUFFER_SIZE) );


	EXPECT_EQ( outputMsgSize , 68 );
	
}

TEST( CMsgSetSpeed,BasicSize_2Motors_Content )
{	
	RBCGateway::CMsgSetSpeed msg(2);
	
	msg.SetAddress(RBCGateway::moduleStepping_1);
	msg.SetSpeedForMotor(0,static_cast<Int32>(0x00FF));
	msg.SetSpeedForMotor(1,static_cast<Int32>(0x0F0F));
	
	Int8 testBuffer[TEST_BUFFER_SIZE];
	
	size_t outputMsgSize( msg.Serialize(testBuffer,TEST_BUFFER_SIZE) );


	EXPECT_EQ( outputMsgSize , 20 );
	EXPECT_EQ( testBuffer[0] , static_cast<Int8>(0xFF ));
	EXPECT_EQ( testBuffer[1] , static_cast<Int8>(0x13 ));
	EXPECT_EQ( testBuffer[2] , static_cast<Int8>(0x20 ));
	// first speed
	EXPECT_EQ( testBuffer[3] , static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[4] , static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[5] , static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[6] , static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[7] , static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[8] , static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[9] , static_cast<Int8>('F' ));
	EXPECT_EQ( testBuffer[10] , static_cast<Int8>('F' ));
	// second speed
	EXPECT_EQ( testBuffer[11] , static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[12] , static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[13] , static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[14] , static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[15] , static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[16] , static_cast<Int8>('F' ));
	EXPECT_EQ( testBuffer[17] , static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[18] , static_cast<Int8>('F' ));
	EXPECT_EQ( testBuffer[19] , static_cast<Int8>(0x0A ));
	
}

