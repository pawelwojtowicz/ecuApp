#include "CMsgSetPosition.h"

namespace RBCGateway
{
CMsgSetPosition::CMsgSetPosition( const UInt8 motorCount)
: CMsgBase(moduleInvalid, cmdSetPosition)
,	m_motorCount(motorCount)
{
	m_positions.resize(m_motorCount);
}

CMsgSetPosition::~CMsgSetPosition()
{
}

void CMsgSetPosition::SetPositionForMotor(const UInt8 motorID, const Int32 position)
{
	if (motorID < m_motorCount)
	{
		m_positions[motorID] = position;
	}
}
	
size_t CMsgSetPosition::GetPayloadSize()
{
	return ( m_motorCount * 8 );
}	

void CMsgSetPosition::SerializePayload()
{
	for( UInt8 motorID = 0 ; motorID < m_motorCount ; ++motorID )
	{
		PutSignedHASCII(m_positions[motorID], 8);
	}
}	
}

