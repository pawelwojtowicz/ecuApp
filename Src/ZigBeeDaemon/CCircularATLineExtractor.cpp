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

		size_t readPosition(m_readPosition);
		for( size_t cnt= m_readContentSize; cnt > 1 ; --cnt )
		{
			if ( m_buffer[readPosition%m_bufferSize]=='\n' && m_buffer[(readPosition+1)%m_bufferSize]=='\r')
			{

				if (readPosition!= m_readPosition)
				{
					std::string command;
					size_t tokenSize(0);					
					if ( readPosition > m_readPosition )
					{
						tokenSize = readPosition-m_readPosition;
						command = std::string(m_buffer+m_readPosition, tokenSize);
					}
					else
					{
						tokenSize = readPosition + m_bufferSize - m_readPosition;
						command = std::string(tokenSize,' ');
						for (size_t idx=0;idx<tokenSize;++idx)
						{
							command[idx]=m_buffer[(m_readPosition+idx)%m_bufferSize];
						}
					}

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
			readPosition = (readPosition+1)%m_bufferSize;		
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
