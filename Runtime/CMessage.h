#ifndef RUNTIME_CMESSAGE_H
#define RUNTIME_CMESSAGE_H
#define MSG_HEADER_SIZE ( sizeof(UInt32) + sizeof(UInt8) + sizeof(UInt32) )
#include "../Global/GlobalTypes.h"

namespace Runtime
{
class CMessage
{
public:
	CMessage( const size_t payloadSize );
	CMessage( Int8* buffer, size_t size );
	virtual ~CMessage();

	inline void SetMessageId( const UInt32& msgId ) { m_msgID = msgId; } ; 
	inline const UInt32 GetMessageId() const { return m_msgID; };

	inline void SetMsgPrio( const UInt8 msgPrio ) { m_msgPrio = msgPrio; };
	inline const UInt8 GetMessagePrio() const { return m_msgPrio; } ;

	inline void SetTimeStamp() {};
	inline const UInt32& GetTimeStamp() const { return m_timestamp ; } ;
	
	inline const bool IsValid() const 
	{ 
		return ( m_messageSize >= MSG_HEADER_SIZE );
	} ;

	inline void SetTarget( const UInt32& targetQueueId ) { m_targetQueueId = targetQueueId; };
	inline const UInt32 GetTargetId() const { return m_targetQueueId; };

	void SerializeHeader();
	void DeserializeHeader();

	void ResetPayload()
	{
		m_serializerPosition = m_messageBuffer + MSG_HEADER_SIZE;
	}

	const Int8* GetBuffer() const { return m_messageBuffer; };
	const size_t GetBufferSize() const { return m_messageSize; };

private:
	UInt32 m_msgID;
	UInt8  m_msgPrio;
	UInt32 m_timestamp;
	UInt32 m_targetQueueId;

	size_t m_messageSize;
	Int8* m_messageBuffer;
	bool 	 m_ownBuffer;
	Int8* m_serializerPosition;
};
}

#endif
