#include <gtest/gtest.h>
#include <RBCGateway/RBCTypes.h>
#include <RBCGateway/CMsgResetEncoders.h>

TEST( CMsgResetEncoders,Basic )
{	
	RBCGateway::CMsgResetEncoders msg;
	
	msg.SetAddress(RBCGateway::moduleStepping_1);
	msg.SetMotorID(4);
	
	Int8 testBuffer[25];
	
	size_t outputMsgSize( msg.Serialize(testBuffer,25) );


	EXPECT_EQ( outputMsgSize , 7 );
	
}

TEST( CMsgResetEncoders, MsgContents )
{	
	RBCGateway::CMsgResetEncoders msg;

	msg.SetAddress(RBCGateway::moduleStepping_1);
	msg.SetMotorID(8);
	
	Int8 testBuffer[25];
	
	msg.Serialize(testBuffer,25) ;

	EXPECT_EQ( testBuffer[0] , static_cast<Int8>(0xFF ));
	EXPECT_EQ( testBuffer[1] , static_cast<Int8>(0x13 ));
	EXPECT_EQ( testBuffer[2] , static_cast<Int8>(0x53 ));
	EXPECT_EQ( testBuffer[3] , static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[4] , static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[5] , static_cast<Int8>('8' ));
	EXPECT_EQ( testBuffer[6] , static_cast<Int8>(0x0A ));
	
}


