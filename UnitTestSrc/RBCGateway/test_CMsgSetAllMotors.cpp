#include <gtest/gtest.h>
#include <RBCGateway/CMsgSetAllMotors.h>

TEST( CMsgSetAllMotors,Size )
{	
	RBCGateway::CMsgSetAllMotors msg;
		
	Int8 testBuffer[300];
	
	size_t outputMsgSize( msg.Serialize(testBuffer,300) );

	EXPECT_EQ( outputMsgSize , 260 );	
}

TEST( CMsgSetAllMotors, ContentValidation )
{	
	RBCGateway::CMsgSetAllMotors msg;

	//legid_LeftFront 	= 0x00,
	//legid_RightFront	= 0x01,
	//legid_LeftRear		= 0x02,
	//legid_RightRear		= 0x03
		
	msg.SetDrivingSpeed(RBCGateway::legid_LeftFront, 100);
	msg.SetDrivingSpeed(RBCGateway::legid_RightFront,-100);
	msg.SetDrivingSpeed(RBCGateway::legid_LeftRear,299);
	msg.SetDrivingSpeed(RBCGateway::legid_RightRear,-299);

	msg.SetSteeringPosition(RBCGateway::legid_LeftFront, 100);
	msg.SetSteeringPosition(RBCGateway::legid_RightFront,-100);
	msg.SetSteeringPosition(RBCGateway::legid_LeftRear,299);
	msg.SetSteeringPosition(RBCGateway::legid_RightRear,-299);
	
	Int8 testBuffer[300];

	size_t outputMsgSize( msg.Serialize(testBuffer,300) );

	EXPECT_EQ( testBuffer[0] , static_cast<Int8>(0xFF) );
	EXPECT_EQ( testBuffer[1] , static_cast<Int8>(RBCGateway::moduleHUB) );
	EXPECT_EQ( testBuffer[2] , static_cast<Int8>(RBCGateway::cmdSetAllMotors) );
	
	// hascii of the left front driving speed
	EXPECT_EQ( testBuffer[3] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[4] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[5] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[6] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[7] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[8] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[9] , static_cast<Int8>('6') );
	EXPECT_EQ( testBuffer[10] , static_cast<Int8>('4') );
	//hascii of the left front driving position
	EXPECT_EQ( testBuffer[11] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[12] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[13] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[14] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[15] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[16] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[17] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[18] , static_cast<Int8>('0') );
	
	//hascii right front speed
	EXPECT_EQ( testBuffer[19] , static_cast<Int8>('F') );
	EXPECT_EQ( testBuffer[20] , static_cast<Int8>('F') );
	EXPECT_EQ( testBuffer[21] , static_cast<Int8>('F') );
	EXPECT_EQ( testBuffer[22] , static_cast<Int8>('F') );
	EXPECT_EQ( testBuffer[23] , static_cast<Int8>('F') );
	EXPECT_EQ( testBuffer[24] , static_cast<Int8>('F') );
	EXPECT_EQ( testBuffer[25] , static_cast<Int8>('9') );
	EXPECT_EQ( testBuffer[26] , static_cast<Int8>('C') );

	//hascii right front position
	EXPECT_EQ( testBuffer[27] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[28] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[29] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[30] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[31] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[32] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[33] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[34] , static_cast<Int8>('0') );

	//hascii left rear speed
	EXPECT_EQ( testBuffer[35] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[36] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[37] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[38] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[39] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[40] , static_cast<Int8>('1') );
	EXPECT_EQ( testBuffer[41] , static_cast<Int8>('2') );
	EXPECT_EQ( testBuffer[42] , static_cast<Int8>('B') );

	//hascii left rear position
	EXPECT_EQ( testBuffer[43] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[44] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[45] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[46] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[47] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[48] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[49] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[50] , static_cast<Int8>('0') );

	//hascii right rear speed
	EXPECT_EQ( testBuffer[51] , static_cast<Int8>('F') );
	EXPECT_EQ( testBuffer[52] , static_cast<Int8>('F') );
	EXPECT_EQ( testBuffer[53] , static_cast<Int8>('F') );
	EXPECT_EQ( testBuffer[54] , static_cast<Int8>('F') );
	EXPECT_EQ( testBuffer[55] , static_cast<Int8>('F') );
	EXPECT_EQ( testBuffer[56] , static_cast<Int8>('E') );
	EXPECT_EQ( testBuffer[57] , static_cast<Int8>('D') );
	EXPECT_EQ( testBuffer[58] , static_cast<Int8>('5') );

	//hascii right rear position
	EXPECT_EQ( testBuffer[59] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[60] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[61] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[62] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[63] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[64] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[65] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[66] , static_cast<Int8>('0') );
	
	//steering
	// hascii of the left front steering speed
	EXPECT_EQ( testBuffer[67] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[68] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[69] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[70] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[71] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[72] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[73] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[74] , static_cast<Int8>('0') );
	//hascii of the left front driving position
	EXPECT_EQ( testBuffer[75] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[76] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[77] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[78] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[79] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[80] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[81] , static_cast<Int8>('6') );
	EXPECT_EQ( testBuffer[82] , static_cast<Int8>('4') );
	
	//hascii right front speed
	EXPECT_EQ( testBuffer[83] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[84] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[85] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[86] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[87] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[88] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[89] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[90] , static_cast<Int8>('0') );

	//hascii right front position
	EXPECT_EQ( testBuffer[91] , static_cast<Int8>('F') );
	EXPECT_EQ( testBuffer[92] , static_cast<Int8>('F') );
	EXPECT_EQ( testBuffer[93] , static_cast<Int8>('F') );
	EXPECT_EQ( testBuffer[94] , static_cast<Int8>('F') );
	EXPECT_EQ( testBuffer[95] , static_cast<Int8>('F') );
	EXPECT_EQ( testBuffer[96] , static_cast<Int8>('F') );
	EXPECT_EQ( testBuffer[97] , static_cast<Int8>('9') );
	EXPECT_EQ( testBuffer[98] , static_cast<Int8>('C') );

	//hascii left rear speed
	EXPECT_EQ( testBuffer[99] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[100] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[101] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[102] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[103] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[104] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[105] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[106] , static_cast<Int8>('0') );

	//hascii left rear position
	EXPECT_EQ( testBuffer[107] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[108] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[109] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[110] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[111] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[112] , static_cast<Int8>('1') );
	EXPECT_EQ( testBuffer[113] , static_cast<Int8>('2') );
	EXPECT_EQ( testBuffer[114] , static_cast<Int8>('B') );

	//hascii right rear speed
	EXPECT_EQ( testBuffer[115] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[116] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[117] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[118] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[119] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[120] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[121] , static_cast<Int8>('0') );
	EXPECT_EQ( testBuffer[122] , static_cast<Int8>('0') );

	//hascii right rear position
	EXPECT_EQ( testBuffer[123] , static_cast<Int8>('F') );
	EXPECT_EQ( testBuffer[124] , static_cast<Int8>('F') );
	EXPECT_EQ( testBuffer[125] , static_cast<Int8>('F') );
	EXPECT_EQ( testBuffer[126] , static_cast<Int8>('F') );
	EXPECT_EQ( testBuffer[127] , static_cast<Int8>('F') );
	EXPECT_EQ( testBuffer[128] , static_cast<Int8>('E') );
	EXPECT_EQ( testBuffer[129] , static_cast<Int8>('D') );
	EXPECT_EQ( testBuffer[130] , static_cast<Int8>('5') );	
	
	EXPECT_EQ( testBuffer[outputMsgSize -1] , static_cast<Int8>( 0x0A) );	

}
