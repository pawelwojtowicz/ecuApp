#pragma once
#include <Global/GlobalTypes.h>

namespace ZigBeeDeamon
{
class IATLineConsumer;

class CCircularATLineExtractor
{
public:
	CCircularATLineExtractor( size_t bufferSize, IATLineConsumer* pATLineConsumer );
	virtual ~CCircularATLineExtractor();

	bool WriteBuffer( Int8* inputBuffer, size_t inputSize);

private:
	CCircularATLineExtractor(const CCircularATLineExtractor&);
	CCircularATLineExtractor& operator=(const CCircularATLineExtractor&);

	size_t m_bufferSize;

	Int8* m_buffer;

	size_t m_writePosition;

	size_t m_readPosition;

	IATLineConsumer* m_pATLineConsumer;
};
}
