#ifndef RBCGATEWAY_CMSGSETALLMOTORS_H
#define RBCGATEWAY_CMSGSETALLMOTORS_H
#include "CMsgBase.h"

namespace RBCGateway
{
class CMsgSetAllMotors : public CMsgBase
{
	typedef std::vector<Int32> tMotorVariable;
public:
	CMsgSetAllMotors();
	virtual ~CMsgSetAllMotors();
	
	void SetDrivingSpeed(tLegId leg, Int32 value);
	void SetDrivingPosition(tLegId leg, Int32 value);

	void SetSteeringSpeed(tLegId leg, Int32 value);
	void SetSteeringPosition(tLegId leg, Int32 value);

	void SetLevelingSpeed(tLegId leg, Int32 value);
	void SetLevelingPosition(tLegId leg, Int32 value);

	void SetSteppingSpeed(tLegId leg, Int32 value);
	void SetSteppingPosition(tLegId leg, Int32 value);

private:
	virtual size_t GetPayloadSize();
	
	virtual void SerializePayload();

private:
	tMotorVariable m_driveSpeed;
	tMotorVariable m_drivePosition;
	
	tMotorVariable m_steeringSpeed;
	tMotorVariable m_steeringPosition;
	
	tMotorVariable m_levelingSpeed;
	tMotorVariable m_levelingPosition;
	
	tMotorVariable m_steppingSpeed;
	tMotorVariable m_steppingPosition;
};
}
#endif //RBCGATEWAY_CMSGSETALLMOTORS_H
