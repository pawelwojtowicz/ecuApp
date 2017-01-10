#include "CSerialPortHandler.h"

#define CIRCULAR_BUFFER_SIZE 256
#define READ_BUFFER_SIZE 64

namespace ATProtocolEngine
{
CSerialPortHandler::CSerialPortHandler()
: m_portName()
, m_portConfiguration()
, m_run(true)
, m_serialPort()
, m_atLineExtrator( CIRCULAR_BUFFER_SIZE, this)

{
}

CSerialPortHandler::~CSerialPortHandler()
{
}

bool CSerialPortHandler::Initialize( const std::string& portName, std::string& portConfiguration)
{
	m_portName = portName;
	m_portConfiguration = portConfiguration;

	if ( m_portName.empty() || m_portConfiguration.empty() )
	{
		return false;
	}

	return true;
}

void CSerialPortHandler::Shutdown()
{
	if (m_run)
	{
		m_run= false;
		if ( !WaitFor() )
		{	
			Terminate();
		}
	}

	if ( m_serialPort.IsValid() )
	{
		m_serialPort.Close();
	}
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

bool CSerialPortHandler::OpenPort()
{
	if (m_serialPort.Open(m_portName) && m_serialPort.Configure(m_portConfiguration) )
	{
		return true;
	}
	return false;

}

void CSerialPortHandler::ClosePort()
{
	m_serialPort.Close();
}

void CSerialPortHandler::StartProcessing()
{
	Start();
}

void CSerialPortHandler::StopProcessing()
{
	m_run= false;
	if ( !WaitFor() )
	{	
		Terminate();
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
