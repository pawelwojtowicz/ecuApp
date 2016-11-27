#include "CCircularATLineExtractor.h"
#include "IATLineConsumer.h"

namespace ZigBeeDeamon
{

CCircularATLineExtractor::CCircularATLineExtractor( size_t bufferSize, IATLineConsumer* pATLineConsumer )
: m_bufferSize(bufferSize)
, m_buffer(new Int8[m_bufferSize])
, m_writePosition(0)
, m_readPosition(0)
, m_pATLineConsumer(pATLineConsumer)
{
}

CCircularATLineExtractor::~CCircularATLineExtractor()
{
	delete [] m_buffer;
	m_bufferSize = 0;
	m_writePosition = 0;
	m_readPosition = 0;
}

bool CCircularATLineExtractor::WriteBuffer( Int8* inputBuffer, size_t inputSize)
{
}

}
