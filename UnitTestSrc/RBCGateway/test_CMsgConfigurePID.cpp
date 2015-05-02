#include <gtest/gtest.h>
#include <RBCGateway/CMsgConfigurePID.h>

TEST( CMsgConfigurePID,Size )
{	
	RBCGateway::CMsgConfigurePID msg;
		
	Int8 testBuffer[300];
	
	size_t outputMsgSize( msg.Serialize(testBuffer,300) );

	EXPECT_EQ( outputMsgSize , 15 );	
}
