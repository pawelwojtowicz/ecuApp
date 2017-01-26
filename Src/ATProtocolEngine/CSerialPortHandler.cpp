#include "CSerialPortHandler.h"
#include <Logger/Logger.h>

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
, m_pATLineConsumer(0)
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

	return false;
}

void CSerialPortHandler::RegisterATLineConsumer( IATLineConsumer* pConsumer)
{
	m_pATLineConsumer = pConsumer;
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
	RETAILMSG(DATA, ("CSerialPortHandler::Started the thread %d", m_run));

	while(m_run)
	{
		toRead = m_atLineExtrator.GetRemainingSpaceSize();

		if (toRead > READ_BUFFER_SIZE)
		{
			toRead = READ_BUFFER_SIZE;
		}
		
		RETAILMSG(DATA, ("I will read %d", toRead));
		if ( 	m_serialPort.WaitRxDataAvailable( 1 ) )
		{
			bytesRead = m_serialPort.Read(inputBuffer, toRead );
	
			m_atLineExtrator.WriteBuffer( inputBuffer, bytesRead );
		}
	}
}

bool CSerialPortHandler::OpenPort()
{
	if (m_serialPort.Open(m_portName) && m_serialPort.Configure(m_portConfiguration) )
	{
		RETAILMSG(INFO, ("Serial port opened succesfully"))
		return true;
	}
	RETAILMSG(ERROR, ("Failed to open Serial port"))

	return false;

}

void CSerialPortHandler::ClosePort()
{
	m_serialPort.Close();
}

void CSerialPortHandler::StartProcessing()
{
	RETAILMSG(DATA, ("CSerialPortHandler::StartProcessing()"));

	Start();
}

void CSerialPortHandler::StopProcessing()
{
	RETAILMSG(DATA, ("CSerialPortHandler::StopProcessing()"));
	m_run= false;
	if ( !WaitFor() )
	{	
		Terminate();
	}
}


bool CSerialPortHandler::SendCommand( const std::string& serializedCommand )
{
	RETAILMSG(DATA, ("Sending command [%s]", serializedCommand.c_str()));
	Int32 charactersToSend( serializedCommand.length() );
	return ( charactersToSend == m_serialPort.Write( static_cast<const Int8*>(serializedCommand.c_str()) , charactersToSend ) );
}

void CSerialPortHandler::NotifyATResponseExtracted( const std::string line )
{
	if (0 != m_pATLineConsumer)
	{
		RETAILMSG(DATA, ("Received response [%s]", line.c_str()));

		m_pATLineConsumer->NotifyATResponseExtracted( line );
	}
}

void CSerialPortHandler::NotifyATPromptExtracted( const std::string line )
{
	if (0 != m_pATLineConsumer)
	{
		RETAILMSG(DATA, ("Received prompt [%s]", line.c_str()));

		m_pATLineConsumer->NotifyATPromptExtracted( line );
	}
}

}
