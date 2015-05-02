#include "CMsgConfigurePID.h"

namespace RBCGateway
{

CMsgConfigurePID::CMsgConfigurePID()
: CMsgBase( moduleInvalid, cmdConfigurePID )
,	m_motorID(0)
, m_controlMode(ctrlModeSpeed)
, m_pidGainType(ctrlPID_Proportional)
, m_gainValue(0)
{
}

CMsgConfigurePID::~CMsgConfigurePID()
{
}
	
void CMsgConfigurePID::SetMotorID(const UInt8 motorID)
{
	m_motorID = motorID;
}

void CMsgConfigurePID::SetControlMode(const tControlMode mode)
{
	m_controlMode = mode;
}
	
void CMsgConfigurePID::SetPIDGainType( const tControlPIDGainType gainType )
{
	m_pidGainType = gainType;
}

void CMsgConfigurePID::SetPIDGain(const Int32 value)
{
	m_gainValue = value;
}	

size_t CMsgConfigurePID::GetPayloadSize()
{
	return 11;
}
	
void CMsgConfigurePID::SerializePayload()
{
	PutUnsignedHASCII(static_cast<UInt32>(m_motorID), 1);
	PutUnsignedHASCII(static_cast<UInt32>((m_controlMode==ctrlModeSpeed)? 0 : 1), 1);
	PutUnsignedHASCII(static_cast<UInt32>(m_pidGainType), 1);
	PutSignedHASCII(static_cast<Int32>(m_gainValue) , 8);
}
	
}
