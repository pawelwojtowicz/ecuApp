#include "CRBCSendThread.h"
#include "CInitSequenceFileParser.h"
#include "CMsgFactory.h"
#include <UCL/CSerialPort.h>
#include <JoystickInterface/CJoyState.h>
#include <JoystickInterface/CJoystickProxy.h>
#include "CMsgSetAllMotors.h"
#include <UCL/SystemEnvironment.h>
#include <unistd.h>
#include <Logger/Logger.h>


#define OUTPUT_BUFFER_SIZE 300

namespace RBCGateway
{
CRBCSendThread::CRBCSendThread( UCL::CSerialPort& rSerialPort, Joystick::CJoystickProxy& joystick )
: m_run(true)
, m_initialized(false)
, m_rSerialPort(rSerialPort)
, m_joystickProxy(joystick)
{
}

CRBCSendThread::~CRBCSendThread()
{
}

void CRBCSendThread::Initialize()
{
  CMsgFactory messageFactory;
  CInitSequenceFileParser initSequenceParser(messageFactory);
  
	std::string iniFileName(UCL::SystemEnvironment::ResolvePath(UCL::SystemEnvironment::Dir_Config, "test.txt"));
	
	RETAILMSG(INFO, ("InitSequence from [%s]", iniFileName.c_str()));
  
  m_initSequence = initSequenceParser.ParseFile(iniFileName);

	Start();
}

void CRBCSendThread::Shutdown()
{
	m_run = false;
	WaitFor();
}
	
void CRBCSendThread::Run()
{
	CMsgSetAllMotors rtControlMessage;

	while(m_run)
	{
		if (m_initialized)
		{
			Joystick::CJoyState joystate;
    
    	m_joystickProxy.GetJoystickState(joystate);
    	
    	usleep( 100 * 1000 );
    	SendMessage(&rtControlMessage);
		}
		else
		{
			for ( tMsgListIterator pMsgIter = m_initSequence.begin(); m_initSequence.end() != pMsgIter ; ++pMsgIter )
			{
				SendMessage(*pMsgIter);
				usleep( 100 * 1000 );

			}
			//execute the initialization sequence;
			m_initialized = true;
		}
	}
}

void CRBCSendThread::SendMessage( CMsgBase* msg)
{
	Int8 outputBuffer[OUTPUT_BUFFER_SIZE];
	size_t bufferSize(OUTPUT_BUFFER_SIZE);
	
	size_t toTransmit( msg->Serialize(outputBuffer, bufferSize ) );
	
	m_rSerialPort.Write(outputBuffer, toTransmit); 
}

}
