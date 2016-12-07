#include "CSerialPortHandler.h"

#define CIRCULAR_BUFFER_SIZE 256
#define READ_BUFFER_SIZE 64

namespace ATProtocolEngine
{
CSerialPortHandler::CSerialPortHandler()
: m_run(true)
, m_serialPort()
, m_atLineExtrator( CIRCULAR_BUFFER_SIZE, this)

{
}

CSerialPortHandler::~CSerialPortHandler()
{
}


bool CSerialPortHandler::Initialize()
{
	std::string portName("com1");
	std::string portConfiguration("taki config");

	if (m_serialPort.Open(portName) && m_serialPort.Configure(portConfiguration) )
	{
		Start();
	}

	return true;
}

void CSerialPortHandler::Shutdown()
{
	m_run= false;
	if ( !WaitFor() )
	{	
		Terminate();
	}

	m_serialPort.Close();
}

void CSerialPortHandler::Run()
{
	Int32 toRead(0);
	size_t bytesRead(0);
	Int8 inputBuffer[READ_BUFFER_SIZE];
	while(m_run)
	{
		toRead = m_atLineExtrator.GetRemainingSpaceSize();

		if (toRead > READ_BUFFER_SIZE)
		{
			toRead = READ_BUFFER_SIZE;
		}

		bytesRead = m_serialPort.Read(inputBuffer, toRead );
	
		m_atLineExtrator.WriteBuffer( inputBuffer, bytesRead );
	}
}

bool CSerialPortHandler::SendCommand( const std::string& serializeCommand )
{
	return true;
}

void CSerialPortHandler::NotifyATResponseExtracted( const std::string line )
{
}

void CSerialPortHandler::NotifyATPromptExtracted( const std::string line )
{
}

}
