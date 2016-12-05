#pragma once
#include <Global/GlobalTypes.h>

namespace ATProtocolEngine
{
class IATLineConsumer;

class CCircularATLineExtractor
{
public:
	CCircularATLineExtractor( size_t bufferSize, IATLineConsumer* pATLineConsumer );
	virtual ~CCircularATLineExtractor();

	bool WriteBuffer(Int8* buffer, size_t chunkSize);
	size_t GetRemainingSpaceSize();

	void PrintHEX();

private:
	CCircularATLineExtractor(const CCircularATLineExtractor&);
	CCircularATLineExtractor& operator=(const CCircularATLineExtractor&);

	size_t m_bufferSize;

	Int8* m_buffer;

	size_t m_writeBufferSpace;

	size_t m_readContentSize;

	size_t m_writePosition;

	size_t m_readPosition;

	IATLineConsumer* m_pATLineConsumer;
};
}
