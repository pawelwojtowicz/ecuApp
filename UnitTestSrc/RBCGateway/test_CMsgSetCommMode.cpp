#include <gtest/gtest.h>
#include <RBCGateway/CMsgSetCommMode.h>

TEST( CMsgSetCommMode,Basic )
{	
	RBCGateway::CMsgSetCommMode msg;
	
	msg.SetCommunicationMode(RBCGateway::mode_Stream);
	
	Int8 testBuffer[25];
	
	size_t outputMsgSize( msg.Serialize(testBuffer,25) );


	EXPECT_EQ( outputMsgSize , 7 );
	
}

TEST( CMsgSetCommMode, SetStreamMode )
{	
	RBCGateway::CMsgSetCommMode msg;
	
	msg.SetCommunicationMode(RBCGateway::mode_Stream);
	
	Int8 testBuffer[25];
	
	msg.Serialize(testBuffer,25) ;

	EXPECT_EQ( testBuffer[0] , static_cast<Int8>(0xFF ));
	EXPECT_EQ( testBuffer[1] , static_cast<Int8>(0x11 ));
	EXPECT_EQ( testBuffer[2] , static_cast<Int8>(0x30 ));
	EXPECT_EQ( testBuffer[3] , static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[4] , static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[5] , static_cast<Int8>('1' ));
	EXPECT_EQ( testBuffer[6] , static_cast<Int8>(0x0A ));
	
}

TEST( CMsgSetCommMode, SetTransparentModeMode )
{	
	RBCGateway::CMsgSetCommMode msg;
	
	msg.SetCommunicationMode(RBCGateway::mode_Transparent);
	
	Int8 testBuffer[25];
	
	msg.Serialize(testBuffer,25) ;

	EXPECT_EQ( testBuffer[0] , static_cast<Int8>(0xFF) );
	EXPECT_EQ( testBuffer[1] , static_cast<Int8>(0x11 ));
	EXPECT_EQ( testBuffer[2] , static_cast<Int8>(0x30) );
	EXPECT_EQ( testBuffer[3] , static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[4] , static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[5] , static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[6] , static_cast<Int8>(0x0A ));
}
