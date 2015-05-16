#ifndef RBCGATEWAY_CMsgSetMotorPosition_H
#define RBCGATEWAY_CMsgSetMotorPosition_H
#include "CMsgBase.h"

namespace RBCGateway
{
class CMsgSetMotorPosition : public CMsgBase
{
public:
	CMsgSetMotorPosition();
	virtual ~CMsgSetMotorPosition();
	
	void SetMotorID(const UInt8 motorID);
	void SetPosition(const Int32 position);
	
private:
	virtual size_t GetPayloadSize();	
	virtual void SerializePayload();
	
private:
	CMsgSetMotorPosition(const CMsgSetMotorPosition&);
	CMsgSetMotorPosition& operator=(const CMsgSetMotorPosition&);
	
	UInt8 m_motorID;
	Int32 m_position;	
};
}
#endif
