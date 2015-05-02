#include "CMsgSetControlMode.h"

namespace RBCGateway
{
CMsgSetControlMode::CMsgSetControlMode()
: CMsgBase( moduleInvalid, cmdSetControlMode )
,m_motorID(0)
,m_controlMode(ctrlModeNoPWM)
{
}

CMsgSetControlMode::~CMsgSetControlMode()
{
}
	
void CMsgSetControlMode::SetMotorID(const UInt8 motorID)
{
	m_motorID = motorID;
}

void CMsgSetControlMode::SetControlMode(const tControlMode controlMode)
{
	m_controlMode = controlMode;
}

size_t CMsgSetControlMode::GetPayloadSize()
{
	return 11;
}
	
void CMsgSetControlMode::SerializePayload()
{
	PutSignedHASCII(static_cast<Int32>(m_motorID), 3);
	PutSignedHASCII(static_cast<Int32>(m_controlMode), 8);
}

}

