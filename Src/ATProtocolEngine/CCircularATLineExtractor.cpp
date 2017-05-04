#include "CCircularATLineExtractor.h"
#include "IATLineConsumer.h"

#include <cstring>

#define LF 0x0A
#define CR 0x0D

namespace ATProtocolEngine
{

CCircularATLineExtractor::CCircularATLineExtractor( size_t bufferSize, IATLineConsumer* pATLineConsumer )
: m_bufferSize(bufferSize)
, m_buffer(new Int8[m_bufferSize+1])
, m_writeBufferSpace(m_bufferSize)
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

void CCircularATLineExtractor::RegisterControlSequence( const std::string& sequence, bool valuePass, bool explicitPass)
{
	tPromptSequence newElement;
	newElement.controlSequence 	= sequence;
	newElement.sequenceLength 	= sequence.length();
	newElement.explicitPass 		= explicitPass;
	newElement.valuePass 				= valuePass;

	m_sequences.push_back(newElement);
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
			for ( tControlSequencesList::iterator iter = m_sequences.begin() ; iter != m_sequences.end() ; ++iter)
			{
				if ( cnt >= iter->sequenceLength )
				{
					bool patternMatches(true);
					for ( size_t idx = 0; idx < iter->sequenceLength && patternMatches ; ++idx)
					{
						if (iter->controlSequence[idx] != m_buffer[(readPosition+idx)%m_bufferSize])
						{
							patternMatches = false;
						}
					}
					if (patternMatches)
					{
						ExtractItem(readPosition, *iter);
						break;
					}
				}
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

void CCircularATLineExtractor::ExtractItem( size_t readPosition, const tPromptSequence& controlSequence)
{
	if (readPosition!= m_readPosition)
	{
		size_t fullLineLength(0);					
		if ( readPosition > m_readPosition )
		{
			fullLineLength = readPosition-m_readPosition;
		}
		else
		{
			fullLineLength = readPosition + m_bufferSize - m_readPosition;
		}

		size_t tokenSize(fullLineLength);
		size_t readStartPosition(m_readPosition);

		if (m_buffer[m_readPosition]=='<' && tokenSize > 2 && m_buffer[(m_readPosition+tokenSize-1)%m_bufferSize] == '>' )
		{
			tokenSize -=2;
			readStartPosition +=1;
		}
	
		std::string command(tokenSize,' ');										
		for (size_t idx=0;idx<tokenSize;++idx)
		{
			command[idx]=m_buffer[(readStartPosition+idx)%m_bufferSize];
		}

		if (0 != m_pATLineConsumer)
		{
			if (controlSequence.valuePass)
			{
				if ( tokenSize == fullLineLength )
				{
					m_pATLineConsumer->NotifyATResponseExtracted(command);
				}
				else
				{
					m_pATLineConsumer->NotifyATPromptExtracted(command);
				}
			}

			if (controlSequence.explicitPass)
			{
				m_pATLineConsumer->NotifyATPromptExtracted(controlSequence.controlSequence);
			}
		}

		m_readPosition = (m_readPosition+fullLineLength)%m_bufferSize;
		m_writeBufferSpace += fullLineLength;
		m_readContentSize -= 	fullLineLength;

	}

	m_readPosition = (m_readPosition + controlSequence.sequenceLength )%m_bufferSize;
	m_readContentSize -= controlSequence.sequenceLength;
	m_writeBufferSpace += controlSequence.sequenceLength;
}

}
