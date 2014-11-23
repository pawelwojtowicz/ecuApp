#include "CSerializable.h"
#include <cstring>


namespace UCL
{

CSerializable::CSerializable()
: m_bufferSize(0)
, m_buffer(0)
, m_serializerPosition(0)
{
}

CSerializable::~CSerializable()
{
}

size_t CSerializable::Serialize(Int8* buffer, size_t bufferSize)
{
	m_bufferSize = bufferSize;
	m_buffer  = buffer;
	m_serializerPosition = m_buffer;

	return (ToByteStream()? static_cast<UInt32>(m_serializerPosition  - m_buffer) : 0 );
;	
}

bool CSerializable::Deserialize(Int8* buffer, size_t bufferSize)
{
	m_bufferSize = bufferSize;
	m_buffer  = buffer;
	m_serializerPosition = m_buffer;
	
	return FromByteStream();	
}




template<typename TYPE> 
bool CSerializable::SetValueImpl(const TYPE& value )
{
	if ( m_bufferSize - static_cast<UInt32>(m_serializerPosition  - m_buffer) >= sizeof(value) )
	{
		memcpy( m_serializerPosition, &value, sizeof( value ));
		m_serializerPosition += sizeof( value );
		return true;
	}
	return false;
}

template<typename TYPE> bool CSerializable::GetValueImpl( TYPE& value )
{
	if ( m_bufferSize - static_cast<UInt32>(m_serializerPosition  - m_buffer)  >= sizeof(value) )
	{
		memcpy(&value, m_serializerPosition, sizeof( value ));
		m_serializerPosition += sizeof( value );
		return true;
	}
	return false;

}

bool CSerializable::SetValue(const UInt8& value)
{
	return SetValueImpl(value);
}

bool CSerializable::GetValue(UInt8& value)
{
{
	return GetValueImpl(value);
}
}

bool CSerializable::SetValue(const UInt16& value)
{
	return SetValueImpl(value);
}

bool CSerializable::GetValue(UInt16& value)
{
	return GetValueImpl(value);
}

bool CSerializable::SetValue(const UInt32& value)
{
	return SetValueImpl(value);
}

bool CSerializable::GetValue(UInt32& value)
{
	return GetValueImpl(value);
}

bool CSerializable::SetValue(const Int8& value)
{
	return SetValueImpl(value);
}

bool CSerializable::GetValue(Int8& value)
{
	return GetValueImpl(value);
}

bool CSerializable::SetValue(const Int16& value)
{
	return SetValueImpl(value);
}

bool CSerializable::GetValue(Int16& value)
{
	return GetValueImpl(value);
}

bool CSerializable::SetValue(const Int32& value)
{
	return SetValueImpl(value);
}

bool CSerializable::GetValue(Int32& value)
{
	return GetValueImpl(value);
}

bool CSerializable::SetValue(const Real32& value)
{
	return SetValueImpl(value);
}

bool CSerializable::GetValue(Real32& value)
{
	return GetValueImpl(value);
}

bool CSerializable::SetValue(const Real64& value)
{
	return SetValueImpl(value);
}

bool CSerializable::GetValue(Real64& value)
{
	return GetValueImpl(value);
}

bool CSerializable::SetValue(const std::string& value)
{
	UInt8 stringLength(value.length());
	size_t neededSpace = stringLength * sizeof( std::string::value_type ) + sizeof(UInt8);
	if ( m_bufferSize - static_cast<UInt32>(m_serializerPosition  - m_buffer)  >= neededSpace )
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

bool CSerializable::GetValue(std::string& value)
{
	UInt8 stringLength(0);
	if ( GetValue(stringLength) )
	{
		if ( m_bufferSize - static_cast<UInt32>(m_serializerPosition  - m_buffer)  >= stringLength )
		{
			value.assign(m_serializerPosition,stringLength);
			m_serializerPosition += stringLength;
			return true;
		}
	}
	return false;
}

}
