#include "CMessage.h"
#include <cstring>
#include <stdio.h>

namespace Runtime
{

CMessage::CMessage( const size_t payloadSize )
: m_messageSize( MSG_HEADER_SIZE + payloadSize )
, m_messageBuffer( new Int8[m_messageSize] )
, m_ownBuffer(true)
, m_serializerPosition(m_messageBuffer+MSG_HEADER_SIZE)
{
}


CMessage::CMessage( Int8* buffer, size_t size )
: m_messageSize(size)
, m_messageBuffer(buffer)
, m_ownBuffer(false)
, m_serializerPosition(m_messageBuffer+MSG_HEADER_SIZE)

{
}

CMessage::~CMessage()
{
	if (m_ownBuffer)
	{
		delete [] m_messageBuffer;
	}
}

void CMessage::SerializeHeader()
{
	m_serializerPosition = m_messageBuffer;
	memcpy(m_serializerPosition,&m_msgID, sizeof(m_msgID));
	m_serializerPosition += sizeof(m_msgID);
	memcpy(m_serializerPosition, &m_timestamp, sizeof( m_timestamp));
	m_serializerPosition += sizeof(m_timestamp);
}

void CMessage::DeserializeHeader()
{
	m_serializerPosition = m_messageBuffer;
	memcpy(&m_msgID, m_serializerPosition, sizeof(m_msgID));
	m_serializerPosition += sizeof(m_msgID);
	memcpy(&m_timestamp, m_serializerPosition, sizeof( m_timestamp));
	m_serializerPosition += sizeof(m_timestamp);
}

template<typename TYPE> 
bool CMessage::SetValueImpl(const TYPE& value )
{
	if ( m_messageSize - static_cast<UInt32>(m_serializerPosition  - m_messageBuffer) >= sizeof(value) )
	{
		memcpy( m_serializerPosition, &value, sizeof( value ));
		m_serializerPosition += sizeof( value );
		return true;
	}
	return false;
}

template<typename TYPE> bool CMessage::GetValueImpl( TYPE& value )
{
	if ( m_messageSize - static_cast<UInt32>(m_serializerPosition  - m_messageBuffer)  >= sizeof(value) )
	{
		memcpy(&value, m_serializerPosition, sizeof( value ));
		m_serializerPosition += sizeof( value );
		return true;
	}
	return false;

}

bool CMessage::SetValue(const UInt8& value)
{
	return SetValueImpl(value);
}

bool CMessage::GetValue(UInt8& value)
{
{
	return GetValueImpl(value);
}
}

bool CMessage::SetValue(const UInt16& value)
{
	return SetValueImpl(value);
}

bool CMessage::GetValue(UInt16& value)
{
	return GetValueImpl(value);
}

bool CMessage::SetValue(const UInt32& value)
{
	return SetValueImpl(value);
}

bool CMessage::GetValue(UInt32& value)
{
	return GetValueImpl(value);
}

bool CMessage::SetValue(const Int8& value)
{
	return SetValueImpl(value);
}

bool CMessage::GetValue(Int8& value)
{
	return GetValueImpl(value);
}

bool CMessage::SetValue(const Int16& value)
{
	return SetValueImpl(value);
}

bool CMessage::GetValue(Int16& value)
{
	return GetValueImpl(value);
}

bool CMessage::SetValue(const Int32& value)
{
	return SetValueImpl(value);
}

bool CMessage::GetValue(Int32& value)
{
	return GetValueImpl(value);
}

bool CMessage::SetValue(const Real32& value)
{
	return SetValueImpl(value);
}

bool CMessage::GetValue(Real32& value)
{
	return GetValueImpl(value);
}

bool CMessage::SetValue(const Real64& value)
{
	return SetValueImpl(value);
}

bool CMessage::GetValue(Real64& value)
{
	return GetValueImpl(value);
}

bool CMessage::SetValue(const std::string& value)
{
	UInt8 stringLength(value.length());
	size_t neededSpace = stringLength * sizeof( std::string::value_type ) + sizeof(UInt8);
	if ( m_messageSize - static_cast<UInt32>(m_serializerPosition  - m_messageBuffer)  >= neededSpace )
	{
		if ( SetValue(stringLength) )
		{
			memcpy( m_serializerPosition, value.c_str(), stringLength );
			m_serializerPosition += stringLength;
			return true;
		}
	}
	return false;
}

bool CMessage::GetValue(std::string& value)
{
	UInt8 stringLength(0);
	if ( GetValue(stringLength) )
	{
		if ( m_messageSize - static_cast<UInt32>(m_serializerPosition  - m_messageBuffer)  >= stringLength )
		{
			value.assign(m_serializerPosition,stringLength);
			m_serializerPosition += stringLength;
			return true;
		}
	}
	return false;
}

void CMessage::PrintBuffer()
{
	for (UInt32 i = 0 ; i < m_messageSize ; ++i )
	{
		printf("%x ", m_messageBuffer[i]);
	}
	printf("\n");
}
}
