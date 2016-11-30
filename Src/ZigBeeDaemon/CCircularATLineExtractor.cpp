#include "CCircularATLineExtractor.h"
#include "IATLineConsumer.h"

#include <cstring>

namespace ZigBeeDaemon
{

CCircularATLineExtractor::CCircularATLineExtractor( size_t bufferSize, IATLineConsumer* pATLineConsumer )
: m_bufferSize(bufferSize)
, m_buffer(new Int8[m_bufferSize+1])
,	m_writeBufferSpace(m_bufferSize)
, m_readContentSize(0)
, m_writePosition(0)
, m_readPosition(0)
, m_pATLineConsumer(pATLineConsumer)
{
	memset(m_buffer,0, m_bufferSize+1);
}

CCircularATLineExtractor::~CCircularATLineExtractor()
{
	delete [] m_buffer;
	m_bufferSize = 0;
	m_writePosition = 0;
	m_readPosition = 0;
}


bool CCircularATLineExtractor::WriteBuffer(Int8* buffer, size_t chunkSize)
{
	bool retVal(false);
	if (chunkSize <= m_writeBufferSpace )
	{
		for( size_t position = 0 ; position < chunkSize ; ++position )
		{
			m_buffer[(m_writePosition+position)%m_bufferSize] = buffer[position];
		}
		m_writePosition = (m_writePosition+chunkSize)%m_bufferSize;
		m_readContentSize +=chunkSize;
		m_writeBufferSpace -= chunkSize;
		retVal = true;

		PrintHEX();

		size_t iterCount(0);

		for( size_t readPosition= m_readPosition; readPosition+1 < m_readPosition+m_readContentSize; ++readPosition )
		{
			if ( m_buffer[readPosition]=='\n' && m_buffer[readPosition+1]=='\r')
			{

				if (readPosition>m_readPosition)
				{
					size_t tokenSize(readPosition-m_readPosition);
					std::string command(m_buffer+m_readPosition, tokenSize);

					if (0 != m_pATLineConsumer)
					{
						m_pATLineConsumer->NotifyATResponseExtracted(command);
					}

					m_readPosition = (m_readPosition+tokenSize)%m_bufferSize;
					m_writeBufferSpace += tokenSize;
  				m_readContentSize -= (tokenSize);

				}

				m_readPosition = (m_readPosition +2)%m_bufferSize;
				m_readContentSize -=2;
				m_writeBufferSpace +=2;
			}		
		}
	}
	return retVal;
}

size_t CCircularATLineExtractor::GetRemainingSpaceSize()
{
	return m_writeBufferSpace;
}

void CCircularATLineExtractor::PrintHEX()
{
	for (size_t i = 0 ; i < m_bufferSize ; ++i)
	{
		if (i==m_readPosition)
		{
			printf("|");
		}
		else
		{
			printf(" ");
		}
		printf ("%02x ", m_buffer[i]);
	}
	printf("\n");
}

}
