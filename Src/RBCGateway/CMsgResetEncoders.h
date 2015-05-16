#ifndef RBCGATEWAY_CMSGRESETENCODERS_H
#define RBCGATEWAY_CMSGRESETENCODERS_H
#include "CMsgBase.h"

namespace RBCGateway
{
class CMsgResetEncoders: public CMsgBase
{
public:
	CMsgResetEncoders();
	virtual ~CMsgResetEncoders();
	
	void SetMotorID(const UInt8 motorID);

	
private:
	virtual size_t GetPayloadSize();
	
	virtual void SerializePayload();

	
private:
	CMsgResetEncoders(const CMsgResetEncoders&);
	CMsgResetEncoders& operator=(const CMsgResetEncoders&);
	
private:
	UInt8 m_motorID;
};
}
#endif
