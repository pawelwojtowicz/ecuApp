#ifndef RBCGATEWAY_CMSGSETSPEED_H
#define RBCGATEWAY_CMSGSETSPEED_H
#include "CMsgBase.h"

namespace RBCGateway
{
class CMsgSetSpeed : public CMsgBase
{
	typedef std::vector<Int32> tSpeedsVector;
public:
	CMsgSetSpeed(const UInt8 motorCount = 4);
	virtual ~CMsgSetSpeed();
	
	void SetSpeedForMotor(const UInt8 motorID, const Int32 speed);
	
private:
	virtual size_t GetPayloadSize();	
	virtual void SerializePayload();
	
private:
	CMsgSetSpeed(const CMsgSetSpeed&);
	CMsgSetSpeed& operator=(const CMsgSetSpeed&);
	
	UInt8 m_motorCount;
	
	tSpeedsVector m_speeds;
};
}
#endif
