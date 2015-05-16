#include "CMsgSetMotorPosition.h"

namespace RBCGateway
{
CMsgSetMotorPosition::CMsgSetMotorPosition()
: CMsgBase(moduleInvalid, cmdSetMotorPosition)
, m_motorID(0)
, m_position(0)
{
}

CMsgSetMotorPosition::~CMsgSetMotorPosition()
{
}

void CMsgSetMotorPosition::SetMotorID(const UInt8 motorID)
{
	m_motorID = motorID;
}

void CMsgSetMotorPosition::SetPosition(const Int32 position)
{
	m_position = position;
}

	
size_t CMsgSetMotorPosition::GetPayloadSize()
{
	return 11;
}	

void CMsgSetMotorPosition::SerializePayload()
{
	PutSignedHASCII(m_motorID, 3);
	PutSignedHASCII(m_position, 8);
}
	
}

