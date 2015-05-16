#include "CMsgSetMotorSpeed.h"

namespace RBCGateway
{
CMsgSetMotorSpeed::CMsgSetMotorSpeed()
: CMsgBase(moduleInvalid, cmdSetMotorSpeed)
, m_motorID(0)
, m_speed(0)
{
}

CMsgSetMotorSpeed::~CMsgSetMotorSpeed()
{
}

void CMsgSetMotorSpeed::SetMotorID(const UInt8 motorID)
{
	m_motorID = motorID;
}

void CMsgSetMotorSpeed::SetSpeed(const Int32 speed)
{
	m_speed = speed;
}

	
size_t CMsgSetMotorSpeed::GetPayloadSize()
{
	return 11;
}	

void CMsgSetMotorSpeed::SerializePayload()
{
	PutSignedHASCII(m_motorID, 3);
	PutSignedHASCII(m_speed, 8);
}
	
}

