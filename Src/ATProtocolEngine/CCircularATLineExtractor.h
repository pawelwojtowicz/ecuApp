#pragma once
#include <Global/GlobalTypes.h>

namespace ATProtocolEngine
{
class IATLineConsumer;

class CCircularATLineExtractor
{
	struct tPromptSequence
	{
		std::string controlSequence;
		size_t sequenceLength;
		bool explicitPass;
		bool valuePass;
	};

	typedef	std::list<tPromptSequence> tControlSequencesList; 
public:
	CCircularATLineExtractor( size_t bufferSize, IATLineConsumer* pATLineConsumer );
	virtual ~CCircularATLineExtractor();

	void RegisterControlSequence( const std::string& sequence, bool valuePass, bool explicitPass);

	bool WriteBuffer(Int8* buffer, size_t chunkSize);
	size_t GetRemainingSpaceSize();

	void PrintHEX();

private:
	void ExtractItem( size_t readPosition, const tPromptSequence& controlSequence);

private:
	CCircularATLineExtractor(const CCircularATLineExtractor&);
	CCircularATLineExtractor& operator=(const CCircularATLineExtractor&);

	tControlSequencesList m_sequences;

	size_t m_bufferSize;

	Int8* m_buffer;

	size_t m_writeBufferSpace;

	size_t m_readContentSize;

	size_t m_writePosition;

	size_t m_readPosition;

	IATLineConsumer* m_pATLineConsumer;
};
}
