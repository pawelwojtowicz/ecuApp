#ifndef RBCGATEWAY_CMsgSetMotorSpeed_H
#define RBCGATEWAY_CMsgSetMotorSpeed_H
#include "CMsgBase.h"

namespace RBCGateway
{
class CMsgSetMotorSpeed : public CMsgBase
{
public:
	CMsgSetMotorSpeed();
	virtual ~CMsgSetMotorSpeed();
	
	void SetMotorID(const UInt8 motorID);
	void SetSpeed(const Int32 speed);
	
private:
	virtual size_t GetPayloadSize();	
	virtual void SerializePayload();
	
private:
	CMsgSetMotorSpeed(const CMsgSetMotorSpeed&);
	CMsgSetMotorSpeed& operator=(const CMsgSetMotorSpeed&);
	
	UInt8 m_motorID;
	Int32 m_speed;	
};
}
#endif
