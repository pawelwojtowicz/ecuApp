#ifndef RBCGATEWAY_CRBCSENDTHREAD_H
#define RBCGATEWAY_CRBCSENDTHREAD_H
#include <UCL/CThread.h>
#include <JoystickInterface/CJoystickProxy.h>
#include "CMsgBase.h"

namespace UCL
{
class CSerialPort;
}

namespace RBCGateway
{

class CRBCSendThread : UCL::CThread
{
public:
	CRBCSendThread(UCL::CSerialPort& rSerialPort, Joystick::CJoystickProxy& joystick);
	virtual ~CRBCSendThread();
	
	void Initialize();
	void Shutdown();
	
private:
	virtual void Run();
	
	void SendMessage( CMsgBase* msg);

private:
	bool m_run;
	
	bool m_initialized;
	
	UCL::CSerialPort& m_rSerialPort;
	
	Joystick::CJoystickProxy& m_joystickPoxy;
	
	tMsgList m_initSequence;

};
}
#endif
