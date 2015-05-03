#include <gtest/gtest.h>
#include <RBCGateway/CMsgConfigurePID.h>

TEST( CMsgConfigurePID,Size )
{	
	RBCGateway::CMsgConfigurePID msg;
		
	Int8 testBuffer[300];
	
	size_t outputMsgSize( msg.Serialize(testBuffer,300) );

	EXPECT_EQ( outputMsgSize , 15 );	
}

TEST( CMsgConfigurePID, ContentTest )
{	
	RBCGateway::CMsgConfigurePID msg;
	msg.SetMotorID(2);
	msg.SetControlMode(RBCGateway::ctrlModePosition);
	msg.SetPIDGainType( RBCGateway::ctrlPID_Integral );
	msg.SetPIDGain(	123);	

		
	Int8 testBuffer[300];
	size_t outputMsgSize( msg.Serialize(testBuffer,300) );

	EXPECT_EQ( outputMsgSize , 15 );
	EXPECT_EQ( testBuffer[0] , static_cast<Int8>(0xFF) );
	EXPECT_EQ( testBuffer[1] , static_cast<Int8>(RBCGateway::moduleInvalid) );
	EXPECT_EQ( testBuffer[2] , static_cast<Int8>(RBCGateway::cmdConfigurePID) );
	EXPECT_EQ( testBuffer[3] , static_cast<Int8>('2') );
	EXPECT_EQ( testBuffer[4] , static_cast<Int8>('1') );
	EXPECT_EQ( testBuffer[5] , static_cast<Int8>('1') );
	EXPECT_EQ( testBuffer[6] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[7] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[8] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[9] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[10] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[11] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[12] , static_cast<Int8>('7') );
	EXPECT_EQ( testBuffer[13] , static_cast<Int8>('B') );
	EXPECT_EQ( testBuffer[14] , static_cast<Int8>(0x0A) );
}
