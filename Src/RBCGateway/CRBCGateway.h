#ifndef RBCGATEWAY_CRBCGATEWAY_H
#define RBCGATEWAY_CRBCGATEWAY_H
#include <Runtime/CRuntimeUnit.h>
#include <UCL/CSerialPort.h>
#include <TTSInterface/CTTSProxy.h>
#include <JoystickInterface/CJoystickProxy.h>
#include "CRBCSendThread.h"

namespace RBCGateway
{
class CRBCGateway : public Runtime::CRuntimeUnit
{
public:
	CRBCGateway();
	virtual ~CRBCGateway();
	
  virtual void Initialize();

	virtual void Shutdown();
private:
	CRBCGateway(const CRBCGateway&);
	CRBCGateway& operator=(const CRBCGateway&);
	
	UCL::CSerialPort m_port;
	
	TTS::CTTSProxy m_ttsProxy;
  
  Joystick::CJoystickProxy m_joystickProxy;
	
	CRBCSendThread m_sendThread;	
};

}
#endif
