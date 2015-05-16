#include <gtest/gtest.h>
#include <RBCGateway/RBCTypes.h>
#include <RBCGateway/CMsgSetMotorSpeed.h>

#define TEST_BUFFER_SIZE 100

TEST( CMsgSetMotorSpeed,BasicSize )
{	
	RBCGateway::CMsgSetMotorSpeed msg;
	
	msg.SetAddress(RBCGateway::moduleStepping_1);
	
	Int8 testBuffer[TEST_BUFFER_SIZE];
	
	size_t outputMsgSize( msg.Serialize(testBuffer,TEST_BUFFER_SIZE) );


	EXPECT_EQ( outputMsgSize , 15 );
}


TEST( CMsgSetMotorSpeed,BasicSize_2Motors_Content )
{	
	RBCGateway::CMsgSetMotorSpeed msg;
	
	msg.SetAddress(RBCGateway::moduleStepping_1);
	msg.SetMotorID(0x0001);
	msg.SetSpeed(0x00FF);
	
	Int8 testBuffer[TEST_BUFFER_SIZE];
	
	size_t outputMsgSize( msg.Serialize(testBuffer,TEST_BUFFER_SIZE) );


	EXPECT_EQ( outputMsgSize 	, 15 );
	EXPECT_EQ( testBuffer[0] 	, static_cast<Int8>(0xFF ));
	EXPECT_EQ( testBuffer[1] 	, static_cast<Int8>(0x13 ));
	EXPECT_EQ( testBuffer[2] 	, static_cast<Int8>(0x20 ));

	EXPECT_EQ( testBuffer[3] 	, static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[4] 	, static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[5] 	, static_cast<Int8>('1' ));
	
	EXPECT_EQ( testBuffer[6] 	, static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[7] 	, static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[8] 	, static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[9] 	, static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[10] , static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[11] , static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[12] , static_cast<Int8>('F' ));
	EXPECT_EQ( testBuffer[13] , static_cast<Int8>('F' ));
	EXPECT_EQ( testBuffer[14] , static_cast<Int8>(0x0A ));
	
}

