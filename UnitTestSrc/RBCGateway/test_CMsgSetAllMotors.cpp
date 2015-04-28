#include <gtest/gtest.h>
#include <RBCGateway/CMsgSetAllMotors.h>

TEST( CMsgSetAllMotors,Size )
{	
	RBCGateway::CMsgSetAllMotors msg;
		
	Int8 testBuffer[300];
	
	size_t outputMsgSize( msg.Serialize(testBuffer,300) );

	EXPECT_EQ( outputMsgSize , 260 );	
}
