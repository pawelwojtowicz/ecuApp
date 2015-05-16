#include "CMsgSetSpeed.h"

namespace RBCGateway
{
CMsgSetSpeed::CMsgSetSpeed( const UInt8 motorCount)
: CMsgBase(moduleInvalid, cmdSetSpeed)
,	m_motorCount(motorCount)
{
	m_speeds.resize(m_motorCount);
}

CMsgSetSpeed::~CMsgSetSpeed()
{
}

void CMsgSetSpeed::SetSpeedForMotor(const UInt8 motorID, const Int32 speed)
{
	if (motorID < m_motorCount)
	{
		m_speeds[motorID] = speed;
	}
}
	
size_t CMsgSetSpeed::GetPayloadSize()
{
	return ( m_motorCount * 8 );
}	

void CMsgSetSpeed::SerializePayload()
{
	for( UInt8 motorID = 0 ; motorID < m_motorCount ; ++motorID )
	{
		PutSignedHASCII(m_speeds[motorID], 8);
	}
}
	
};

