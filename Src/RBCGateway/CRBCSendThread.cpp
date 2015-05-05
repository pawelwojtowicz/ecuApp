#include "CRBCSendThread.h"
#include "CInitSequenceFileParser.h"
#include "CMsgFactory.h"
#include <UCL/CSerialPort.h>

#define OUTPUT_BUFFER_SIZE 300

namespace RBCGateway
{
CRBCSendThread::CRBCSendThread( UCL::CSerialPort& rSerialPort)
: m_run(true)
, m_initialized(false)
, m_rSerialPort(rSerialPort)
{
}

CRBCSendThread::~CRBCSendThread()
{
}

void CRBCSendThread::Initialize()
{
  CMsgFactory messageFactory;
  CInitSequenceFileParser initSequenceParser(messageFactory);
  
 	std::string iniFileName("test.txt");
  
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
	while(m_run)
	{
		if (m_initialized)
		{
			// read the joystick and send all motor message
		}
		else
		{
			for ( tMsgListIterator pMsgIter = m_initSequence.begin(); m_initSequence.end() != pMsgIter ; ++pMsgIter )
			{
				SendMessage(*pMsgIter);
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
