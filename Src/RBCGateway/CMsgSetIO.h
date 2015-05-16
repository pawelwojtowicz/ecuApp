#ifndef RBCGATEWAY_CMSGSETIO_H
#define RBCGATEWAY_CMSGSETIO_H
#include "CMsgBase.h"

namespace RBCGateway
{
class CMsgSetIO: public CMsgBase
{
public:
	CMsgSetIO();
	virtual ~CMsgSetIO();
	
	void SetPort(const UInt8 portID);
	void SetIO( const UInt8 ioID, const bool ioState);
	
private:
	virtual size_t GetPayloadSize();	
	virtual void SerializePayload();
	
private:
	CMsgSetIO(const CMsgSetIO&);
	CMsgSetIO& operator=(const CMsgSetIO&);
private:
	
	UInt8 m_portID;
	UInt8 m_ioState;
};
}

#endif
