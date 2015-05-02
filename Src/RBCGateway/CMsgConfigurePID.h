#ifndef RBCGateway_CMsgConfigurePID
#define RBCGateway_CMsgConfigurePID
#include "CMsgBase.h"

namespace RBCGateway
{
class CMsgConfigurePID : public CMsgBase
{
public:
	CMsgConfigurePID();
	virtual ~CMsgConfigurePID();
	
	void SetMotorID(const UInt8 motorID);
	void SetControlMode(const tControlMode mode);
	void SetPIDGainType( const tControlPIDGainType gainType );
	void SetPIDGain(const Int32);	
private:
	virtual size_t GetPayloadSize();
	
	virtual void SerializePayload();
	
private:
	UInt8 m_motorID;
	
	tControlMode m_controlMode;
	
	tControlPIDGainType m_pidGainType;
	
	Int32 m_gainValue;
};
}
#endif
