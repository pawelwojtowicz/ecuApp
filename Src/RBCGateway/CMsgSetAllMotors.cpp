#include "CMsgSetAllMotors.h"

namespace RBCGateway
{

CMsgSetAllMotors::CMsgSetAllMotors()
: CMsgBase( moduleHUB, cmdSetAllMotors )
{
	m_driveSpeed.resize(4);
	m_drivePosition.resize(4);
	m_steeringSpeed.resize(4);
	m_steeringPosition.resize(4);
	m_levelingSpeed.resize(4);
	m_levelingPosition.resize(4);
	m_steppingSpeed.resize(4);
	m_steppingPosition.resize(4);
}
	
CMsgSetAllMotors::~CMsgSetAllMotors()
{
}

size_t CMsgSetAllMotors::GetPayloadSize()
{
	return 256;
}
	
void CMsgSetAllMotors::SerializePayload()
{
	for ( UInt8 i = 0 ; i < 4 ; ++i)
	{
		PutSignedHASCII(m_driveSpeed[i], 8);
		PutSignedHASCII(m_drivePosition[i],8);
	}
	
	for ( UInt8 i = 0 ; i < 4 ; ++i)
	{
		PutSignedHASCII(m_steeringSpeed[i], 8);
		PutSignedHASCII(m_steeringPosition[i],8);
	}

	for ( UInt8 i = 0 ; i < 4 ; ++i)
	{
		PutSignedHASCII(m_levelingSpeed[i], 8);
		PutSignedHASCII(m_levelingPosition[i],8);
	}

	for ( UInt8 i = 0 ; i < 4 ; ++i)
	{
		PutSignedHASCII(m_steppingSpeed[i], 8);
		PutSignedHASCII(m_steppingPosition[i],8);
	}
}

void CMsgSetAllMotors::SetDrivingSpeed(tLegId leg, Int32 value)
{
	m_driveSpeed[static_cast<UInt8>(leg)] = value;
}

void CMsgSetAllMotors::SetDrivingPosition(tLegId leg, Int32 value)
{
	m_drivePosition[static_cast<UInt8>(leg)] = value;
}

void CMsgSetAllMotors::SetSteeringSpeed(tLegId leg, Int32 value)
{
	m_steeringSpeed[static_cast<UInt8>(leg)] = value;
}

void CMsgSetAllMotors::SetSteeringPosition(tLegId leg, Int32 value)
{
	m_steeringPosition[static_cast<UInt8>(leg)] = value;
}

void CMsgSetAllMotors::SetLevelingSpeed(tLegId leg, Int32 value)
{
	m_levelingSpeed[static_cast<UInt8>(leg)] = value;
}

void CMsgSetAllMotors::SetLevelingPosition(tLegId leg, Int32 value)
{
	m_levelingPosition[static_cast<UInt8>(leg)] = value;
}

void CMsgSetAllMotors::SetSteppingSpeed(tLegId leg, Int32 value)
{
	m_steppingSpeed[static_cast<UInt8>(leg)] = value;
}

void CMsgSetAllMotors::SetSteppingPosition(tLegId leg, Int32 value)
{
	m_steppingPosition[static_cast<UInt8>(leg)] = value;
}
}

