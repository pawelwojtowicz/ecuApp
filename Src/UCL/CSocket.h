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
	CSocketAddress(const std::string& address)
	{
		memset(&m_addressStruct,0,sizeof(m_addressStruct));
		m_addressStruct.sun_family = AF_UNIX;
		strcpy(m_addressStruct.sun_path,address.c_str());
	}
	
	struct sockaddr_un* GetAddressStructure()
	{
		return &m_addressStruct;
	};
	
	

private:
	struct sockaddr_un m_addressStruct;
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
