#ifndef UCL_CSOCKET_H
#define UCL_CSOCKET_H

#include "GlobalTypes.h"
#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>

namespace UCL
{
class CSocketAddress
{
public:

	CSocketAddress()
	: m_addressStructSize(0)
	{
		memset(&m_addressStruct,0,sizeof(m_addressStruct));
		m_addressStruct.sun_family = AF_UNIX;
		m_addressStructSize = SUN_LEN(&m_addressStruct);
	}

	CSocketAddress(const std::string& address)
	: m_addressStructSize(0)
	{
		memset(&m_addressStruct,0,sizeof(m_addressStruct));
		m_addressStruct.sun_family = AF_UNIX;
		strcpy(m_addressStruct.sun_path,address.c_str());
		m_addressStructSize = SUN_LEN(&m_addressStruct);
	}
	
	struct sockaddr_un* GetAddressStructure()
	{
		return &m_addressStruct;
	};
	
	UInt32 GetAddressSize() const
	{
		return m_addressStructSize;
	}
	
	CSocketAddress( const CSocketAddress& rhs)
	{
		this->m_addressStruct.sun_family = AF_UNIX;
		strcpy( this->m_addressStruct.sun_path,rhs.m_addressStruct.sun_path );
		this->m_addressStructSize = SUN_LEN(&this->m_addressStruct);
	}
	
	CSocketAddress& operator=( const CSocketAddress& rhs)
	{
		this->m_addressStruct.sun_family = AF_UNIX;
		strcpy( this->m_addressStruct.sun_path,rhs.m_addressStruct.sun_path );
		this->m_addressStructSize = SUN_LEN(&this->m_addressStruct);
		return *this;
	}
	
	bool operator==(const CSocketAddress& rhs)
	{
		return (0 == strcmp(this->m_addressStruct.sun_path,rhs.m_addressStruct.sun_path) );
	}
	

private:
	struct sockaddr_un m_addressStruct;
	
	Int32 m_addressStructSize;
};

class CSocket
{
public:
	CSocket();
	virtual ~CSocket();
	
	bool Bind(const std::string& queueName);
	void Close();
	
	bool IsValid();
	
	Int32 Send(CSocketAddress& sockAddress, Int8* buffer, const Int32& bytestToSend);
	Int32 Receive(CSocketAddress& sockAddress, Int8* buffer, const Int32& bytestToSend);

private:
	CSocket(const CSocket&);
	CSocket& operator=(const CSocket&);
	
	Int32 m_socketFileDescriptor;
	
	std::string m_socketName;

};

}

#endif
