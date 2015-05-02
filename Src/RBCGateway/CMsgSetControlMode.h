#ifndef RBCGATEWAY_CMSGSETCONTROLMODE_H
#define RBCGATEWAY_CMSGSETCONTROLMODE_H
#include "CMsgBase.h"


namespace RBCGateway
{
class CMsgSetControlMode : public CMsgBase
{
public:
	CMsgSetControlMode();
	virtual ~CMsgSetControlMode();
	
	void SetMotorID(const UInt8 motorID);
	void SetControlMode(const tControlMode controlMode);

private:
	virtual size_t GetPayloadSize();
	
	virtual void SerializePayload();


private:
	UInt8 m_motorID;
	
	tControlMode m_controlMode;
};

}
#endif
