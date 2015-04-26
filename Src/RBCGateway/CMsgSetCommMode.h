#ifndef RBCGATEWAY_CMSGSETCOMMMODE_H
#define RBCGATEWAY_CMSGSETCOMMMODE_H
#include "CMsgBase.h"

namespace RBCGateway
{
class CMsgSetCommMode : public CMsgBase
{
public:
	CMsgSetCommMode();
	virtual ~CMsgSetCommMode();
	
	void SetCommunicationMode(const tCommunicationMode mode );
	
private:
	virtual size_t GetPayloadSize();
	
	virtual void SerializePayload();
	
private:
	tCommunicationMode m_communicationMode;
};
}
#endif
