#include "CMsgBase.h"
#include <stdio.h>
#include <string.h>

const Int8 s_STX 	=	static_cast<Int8>(0xFF);
const Int8 s_ETX	= static_cast<Int8>(0x0A);

/**
	*	Format of the message:
	*	{STX} {addres} {command} {payload in HASCII} {ETX}
	*  1b      1b       1b    		size of HASCI			1b
	*/ 

namespace RBCGateway
{
CMsgBase::CMsgBase( const tModuleAddress& address, const tCommandCodes& command)
: m_address(address)
, m_command(command)
, m_buffer(0)
,	m_serializationPosition(0)
{
}

CMsgBase::~CMsgBase()
{
}
	
size_t CMsgBase::Serialize( Int8* buffer, const size_t bufferSize )
{
	size_t msgSize(0);
	
	if ( bufferSize >= ( 4 + GetPayloadSize() ) )
	{
		m_buffer = buffer;
		m_serializationPosition = m_buffer;
		
		*(m_serializationPosition++) = s_STX;
		*(m_serializationPosition++) = static_cast<Int8>(m_address);
		*(m_serializationPosition++) = static_cast<Int8>(m_command);

		SerializePayload();

		*(m_serializationPosition++) = static_cast<Int8>(s_ETX);
		
		msgSize = static_cast<size_t>(m_serializationPosition - m_buffer);
	}
	
	return msgSize;
}


void CMsgBase::PutUnsignedHASCII(UInt32 value, size_t hasciiWidth)
{	
	Int8* tmp = m_serializationPosition;
	char formattingString[10];
	sprintf(formattingString,"%%0%dX",hasciiWidth);
	m_serializationPosition += sprintf( m_serializationPosition, formattingString ,  value);
}

}
