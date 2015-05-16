#ifndef RBCGATEWAY_CMsgSetPosition_H
#define RBCGATEWAY_CMsgSetPosition_H
#include "CMsgBase.h"

namespace RBCGateway
{
class CMsgSetPosition : public CMsgBase
{
	typedef std::vector<Int32> tPositionVector;
public:
	CMsgSetPosition(const UInt8 motorCount = 4);
	virtual ~CMsgSetPosition();
	
	void SetPositionForMotor(const UInt8 motorID, const Int32 position);
	
private:
	virtual size_t GetPayloadSize();	
	virtual void SerializePayload();
	
private:
	CMsgSetPosition(const CMsgSetPosition&);
	CMsgSetPosition& operator=(const CMsgSetPosition&);
	
	UInt8 m_motorCount;
	
	tPositionVector m_positions;
};
}
#endif
