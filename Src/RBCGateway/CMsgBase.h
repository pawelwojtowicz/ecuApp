#ifndef RBCGATEWAY_CMSGBASE_H
#define RBCGATEWAY_CMSGBASE_H
#include "RBCTypes.h"

namespace RBCGateway
{
class CMsgBase
{
protected:
	CMsgBase( const tModuleAddress& address, const tCommandCodes& command);
	virtual ~CMsgBase();
	
	virtual size_t GetPayloadSize() = 0;
	
	virtual void SerializePayload() = 0;
	
	void PutUnsignedHASCII(UInt32 value, size_t hasciiWidth);
	
	void PutSignedHASCII(Int32 value, size_t hasciiWidth);
	
public:
	void SetAddress( const tModuleAddress address);
	
	size_t Serialize( Int8* buffer, const size_t bufferSize );
		
private:
	tModuleAddress m_address;
	
	tCommandCodes m_command;
	
	Int8* m_buffer;
	
	Int8* m_serializationPosition;
};

typedef std::list<CMsgBase*> tMsgList;
typedef tMsgList::const_iterator tMsgListIterator;
}
#endif
