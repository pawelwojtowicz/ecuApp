#include "CUDSMockHelper.h"
#include "ISocketMockHelper.h"
#include <UCL/CUnixDomainSocket.h>
#include <Runtime/CMessage.h>
#include <cstring>
namespace UCL
{
CUDSMockHelper::DataPacket::DataPacket(Int8* dataBuffer, Int32 dataSize)
: DataSize(dataSize)
{
	memcpy(Data,dataBuffer,dataSize);
}
		
CUDSMockHelper::DataPacket::DataPacket( const CUDSMockHelper::DataPacket& rhs)
{
	memcpy(Data,rhs.Data, rhs.DataSize);
	DataSize = rhs.DataSize;
}

CUDSMockHelper::DataPacket& CUDSMockHelper::DataPacket::operator=( const CUDSMockHelper::DataPacket& rhs)
{
	memcpy(Data,rhs.Data, rhs.DataSize);
	DataSize = rhs.DataSize;
	return *this;
}
		
bool CUDSMockHelper::DataPacket::operator==(const DataPacket& rhs)
{
	if (DataSize != rhs.DataSize)
	{
		return false;
	}
	
	return ( 0 == memcmp( Data , rhs.Data, rhs.DataSize ) );
}
	


CUDSMockHelper::CUDSMockHelper(ISocketMockHelper* pSocketMockHelper)
: m_mockValid(false)
, m_pSocketMockHelper(pSocketMockHelper)
, m_currentDataPacketIter( m_dataPacketList.begin() )
{

}
	
CUDSMockHelper::~CUDSMockHelper()
{

}

bool CUDSMockHelper::Bind(const std::string& queueName)
{
	if ( 0 != m_pSocketMockHelper )
	{
		m_pSocketMockHelper->Bind(queueName);
	}
	m_mockValid = true;
	
	return m_mockValid;
}

void CUDSMockHelper::Close()
{
	if ( 0 != m_pSocketMockHelper )
	{
		m_pSocketMockHelper->Close();
	}

}
	
bool CUDSMockHelper::IsValid()
{
	if ( 0 != m_pSocketMockHelper )
	{
		m_pSocketMockHelper->IsValid();
	}
	return m_mockValid;

}

bool CUDSMockHelper::IsEmpty()
{
	if ( 0 != m_pSocketMockHelper )
	{
		m_pSocketMockHelper->IsEmpty();
	}
	return (m_currentDataPacketIter == m_dataPacketList.end() );
}


Int32 CUDSMockHelper::Send(CSocketAddress& sockAddress, Int8* buffer, const Int32& bytesToSend)
{
	if ( 0 != m_pSocketMockHelper )
	{
		std::string address(sockAddress.GetAddressStructure()->sun_path);
		if ( bytesToSend > 0 )
		{
			Runtime::CMessage message(buffer, bytesToSend);
			if ( message.IsValid() )
			{
				message.DeserializeHeader();

				tMsgIds msgId = message.GetMessageId();

				m_pSocketMockHelper->Send(address, msgId );
			}
		}
	}
	return bytesToSend;
}

Int32 CUDSMockHelper::Receive(CSocketAddress& sockAddress, Int8* buffer, const Int32& bytestToSend)
{
	Int32 receivedData(0);
	if ( 0 != m_pSocketMockHelper )
	{
		m_pSocketMockHelper->Receive();
	}
	
	if ( m_currentDataPacketIter != m_dataPacketList.end() )
	{
		memcpy( buffer, m_currentDataPacketIter->Data, m_currentDataPacketIter->DataSize);
		
		++m_currentDataPacketIter;
	}
	
	return receivedData;
}

}
