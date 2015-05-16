#include <gtest/gtest.h>
#include <RBCGateway/CMsgSetIO.h>

TEST( CMsgSetIO, Size )
{	
	RBCGateway::CMsgSetIO msg;
		
	Int8 testBuffer[20];
	
	size_t outputMsgSize( msg.Serialize(testBuffer,20) );

	EXPECT_EQ( outputMsgSize , 7 );	
}

TEST( CMsgSetIO, Content_1 )
{	
	RBCGateway::CMsgSetIO msg;
	
	msg.SetAddress(RBCGateway::moduleDrive);
	msg.SetPort(0x04);
	msg.SetIO( 0, true);
	msg.SetIO( 1, true);
	msg.SetIO( 2, true);
	msg.SetIO( 3, true);

		
	Int8 testBuffer[20];
	
	size_t outputMsgSize( msg.Serialize(testBuffer,20) );

	EXPECT_EQ( outputMsgSize , 7 );
	EXPECT_EQ( testBuffer[0], static_cast<Int8>(0xFF ));
	EXPECT_EQ( testBuffer[1], static_cast<Int8>(0x12 ));
	EXPECT_EQ( testBuffer[2], static_cast<Int8>(0x28 ));
	EXPECT_EQ( testBuffer[3], static_cast<Int8>('4' ));
	EXPECT_EQ( testBuffer[4], static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[5], static_cast<Int8>('F' ));
	EXPECT_EQ( testBuffer[6], static_cast<Int8>(0x0A ));
}

TEST( CMsgSetIO, Content_2 )
{	
	RBCGateway::CMsgSetIO msg;
	
	msg.SetAddress(RBCGateway::moduleDrive);
	msg.SetPort(0x04);
	msg.SetIO( 0, true);
	msg.SetIO( 1, true);
	msg.SetIO( 2, true);
	msg.SetIO( 3, true);
	msg.SetIO( 3, false);

		
	Int8 testBuffer[20];
	
	size_t outputMsgSize( msg.Serialize(testBuffer,20) );

	EXPECT_EQ( outputMsgSize , 7 );
	EXPECT_EQ( testBuffer[0], static_cast<Int8>(0xFF ));
	EXPECT_EQ( testBuffer[1], static_cast<Int8>(0x12 ));
	EXPECT_EQ( testBuffer[2], static_cast<Int8>(0x28 ));
	EXPECT_EQ( testBuffer[3], static_cast<Int8>('4' ));
	EXPECT_EQ( testBuffer[4], static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[5], static_cast<Int8>('7' ));
	EXPECT_EQ( testBuffer[6], static_cast<Int8>(0x0A ));
}

TEST( CMsgSetIO, Content_3 )
{	
	RBCGateway::CMsgSetIO msg;
	
	msg.SetAddress(RBCGateway::moduleDrive);
	msg.SetPort(0x04);
	msg.SetIO( 4, true);
	msg.SetIO( 5, true);
	msg.SetIO( 7, true);
		
	Int8 testBuffer[20];
	
	size_t outputMsgSize( msg.Serialize(testBuffer,20) );

	EXPECT_EQ( outputMsgSize , 7 );
	EXPECT_EQ( testBuffer[0], static_cast<Int8>(0xFF ));
	EXPECT_EQ( testBuffer[1], static_cast<Int8>(0x12 ));
	EXPECT_EQ( testBuffer[2], static_cast<Int8>(0x28 ));
	EXPECT_EQ( testBuffer[3], static_cast<Int8>('4' ));
	EXPECT_EQ( testBuffer[4], static_cast<Int8>('B' ));
	EXPECT_EQ( testBuffer[5], static_cast<Int8>('0' ));
	EXPECT_EQ( testBuffer[6], static_cast<Int8>(0x0A ));
}
