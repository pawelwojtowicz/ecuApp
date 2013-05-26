#include "CMessage.h"
#include <cstring>

namespace Runtime
{

CMessage::CMessage( const size_t payloadSize )
: m_messageSize( MSG_HEADER_SIZE + payloadSize )
, m_messageBuffer( new Int8[m_messageSize] )
, m_ownBuffer(true)
{
}


CMessage::CMessage( Int8* buffer, size_t size )
: m_messageSize(size)
, m_messageBuffer(buffer)
, m_ownBuffer(false)
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
	memcpy(m_serializerPosition, &m_msgPrio, sizeof( m_msgPrio));
	m_serializerPosition += sizeof(m_timestamp);
	memcpy(m_serializerPosition, &m_timestamp, sizeof( m_timestamp));
}

void CMessage::DeserializeHeader()
{
	m_serializerPosition = m_messageBuffer;
	memcpy(&m_msgID, m_serializerPosition, sizeof(m_msgID));
	m_serializerPosition += sizeof(m_msgID);
	memcpy(&m_msgPrio, m_serializerPosition, sizeof( m_msgPrio));
	m_serializerPosition += sizeof(m_timestamp);
	memcpy(&m_timestamp, m_serializerPosition, sizeof( m_timestamp));
}

}
