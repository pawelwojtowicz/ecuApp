#ifndef UCL_CUDSMOCKHELPER_H
#define UCL_CUDSMOCKHELPER_H
#include <UCL/IUnixDomainSocket.h>

namespace Runtime
{
class CMessage;
}

namespace UCL
{
class ISocketMockHelper;

class CUDSMockHelper : public IUnixDomainSocket
{
	struct DataPacket
	{
		char Data[250];
		Int32 DataSize;
		
		DataPacket(Int8* dataBuffer, Int32 dataSize);		
		DataPacket( const DataPacket& );
		DataPacket& operator=( const DataPacket&);
		bool operator==(const DataPacket& rhs); 
	};
	
	typedef std::list<DataPacket> tDataPackList;
	typedef tDataPackList::iterator tDataPacketListIterator;
public:
	CUDSMockHelper(ISocketMockHelper* pSocketMockHelper );
	virtual ~CUDSMockHelper();
	
	void EnqueueTestMsg( Runtime::CMessage& message );
	
	void ResetMockState();

private:
	virtual bool Bind(const std::string& queueName);
	virtual void Close();
	
	virtual bool IsValid();
	
	virtual bool IsEmpty();
	
	virtual Int32 Send(CSocketAddress& sockAddress, Int8* buffer, const Int32& bytestToSend);
	virtual Int32 Receive(CSocketAddress& sockAddress, Int8* buffer, const Int32& bytestToSend);

private:
	CUDSMockHelper(const CUDSMockHelper&);
	CUDSMockHelper& operator=(const CUDSMockHelper&);
	
	bool m_mockValid;
	
	ISocketMockHelper* m_pSocketMockHelper;
	
	tDataPackList m_dataPacketList;
	
	tDataPacketListIterator m_currentDataPacketIter;
};
}

#endif
