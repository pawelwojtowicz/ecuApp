#include <gtest/gtest.h>
#include <RBCGateway/CMsgSetControlMode.h>

TEST( CMsgSetControlMode,Size )
{	
	RBCGateway::CMsgSetControlMode msg;
		
	Int8 testBuffer[300];
	
	size_t outputMsgSize( msg.Serialize(testBuffer,300) );

	EXPECT_EQ( outputMsgSize , 15 );	
}
