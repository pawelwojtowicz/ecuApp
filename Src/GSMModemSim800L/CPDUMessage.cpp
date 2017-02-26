#include "CPDUMessage.h"

#define GET_DIGIT(C) (C-'0')

namespace GSMModemSim800L
{
CPDUMessage::CPDUMessage()
: m_valid(false)
, m_smscAddressType(0)
, m_serviceCenter()
, m_senderNumber()
, m_TP_PID(0)
, m_TP_DCS(0)
, m_timestamp()
, m_messageText()
{
}

CPDUMessage::~CPDUMessage()
{
}

const std::string& CPDUMessage::GetServiceCenterNumber() const
{
	return m_serviceCenter;
}

const std::string& CPDUMessage::GetSenderNumber() const
{
	return m_senderNumber;
}


bool CPDUMessage::Deserialize( const std::string& incomingMessage)
{
	m_valid = false;
	size_t messageSize( incomingMessage.length() );
	size_t msgCursor(0);
	if ( messageSize <= 1 )
	{
		return m_valid; 
	}
	
	size_t serviceCenterInfoSize(GET_DIGIT(incomingMessage[msgCursor++])*0x10+GET_DIGIT(incomingMessage[msgCursor++]));

	if ( messageSize - msgCursor < serviceCenterInfoSize*2 )
	{
		return m_valid;
	}

	m_smscAddressType = GET_DIGIT(incomingMessage[msgCursor++])*0x10+GET_DIGIT(incomingMessage[msgCursor++]);

	if (0x91 != m_smscAddressType)
	{
		return m_valid;
	}

	//extracting service center number
	m_serviceCenter = std::string(serviceCenterInfoSize*2-1,'+');
	for ( size_t dgIndex = 1 ; dgIndex < serviceCenterInfoSize ; ++dgIndex )
	{
		if ( incomingMessage[msgCursor] != 'F')
		{
			m_serviceCenter[dgIndex*2] = incomingMessage[msgCursor];
		}
		else
		{
			m_serviceCenter.erase(dgIndex*2);
		}
		msgCursor++;
		m_serviceCenter[dgIndex*2-1] = incomingMessage[msgCursor++];
	}

	//extracting of first octet of this SMS-DELIVER (wtf?)
	msgCursor++;
	msgCursor++;

	//extrating sender number size
	size_t senderAddressSize( ExtractHexDigit(incomingMessage[msgCursor++])*0x10 + ExtractHexDigit(incomingMessage[msgCursor++]) );

	// skip the sender address type for now
	msgCursor++;
	msgCursor++;
	
	m_senderNumber = std::string( senderAddressSize+1 , '+');
	for ( size_t characterCount = 0 ; characterCount < senderAddressSize; ++characterCount )
	{
		if (0==characterCount%2)
		{
			m_senderNumber[characterCount+1] = incomingMessage[characterCount+msgCursor+1];
		}
		else
		{
			m_senderNumber[characterCount+1] = incomingMessage[characterCount+msgCursor-1];
		}
	}

	msgCursor +=senderAddressSize;
	if (senderAddressSize%2)
	{
		++msgCursor;
	}

	m_TP_PID = ExtractHexDigit(incomingMessage[msgCursor++])*0x10 + ExtractHexDigit(incomingMessage[msgCursor++]);
	m_TP_DCS = ExtractHexDigit(incomingMessage[msgCursor++])*0x10 + ExtractHexDigit(incomingMessage[msgCursor++]);

	m_valid = true;
			
	return m_valid;
}

bool CPDUMessage::IsValid() const
{
	return m_valid;
}

UInt8 CPDUMessage::ExtractHexDigit( const char character )
{
	if ( character >='0' && character <='9')
	{
		return character - '0';
	}
	else if (character >= 'A' && character <= 'F' )
	{
		return character - 'A' + 10 ;
	}
	else if (character >= 'a' && character <= 'a' )
	{
		return character - 'a' + 10 ;
	}

	return 0;
}


}
