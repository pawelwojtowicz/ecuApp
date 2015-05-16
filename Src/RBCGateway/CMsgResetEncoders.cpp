#include "CMsgResetEncoders.h"

namespace RBCGateway
{
CMsgResetEncoders::CMsgResetEncoders()
: CMsgBase(moduleInvalid,cmdResetEncoders)
, m_motorID(0)
{
}

CMsgResetEncoders::~CMsgResetEncoders()
{
}


void CMsgResetEncoders::SetMotorID(const UInt8 motorID)
{
	m_motorID = motorID;
}

	
size_t CMsgResetEncoders::GetPayloadSize()
{
	return 3;
}
	
void CMsgResetEncoders::SerializePayload()
{
	PutUnsignedHASCII(static_cast<UInt32>(m_motorID), 3);
}

}
