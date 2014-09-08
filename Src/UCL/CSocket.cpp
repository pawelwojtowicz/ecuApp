#include "CSocket.h"
#include <stdio.h>
#include <errno.h>

namespace UCL
{

CSocket::CSocket()
: m_socketFileDescriptor(-1)
, m_socketName()
{
}

CSocket::~CSocket()
{
}
	
bool CSocket::Bind(const std::string& queueName)
{
	m_socketFileDescriptor = socket(AF_UNIX,SOCK_DGRAM,0);
	
	if ( 0 > m_socketFileDescriptor )
	{
		return false;
	}

	m_socketName = queueName;
	
	unlink(m_socketName.c_str());
	
	//initialize the own address structure
	struct sockaddr_un toBindAddress;
	memset(&toBindAddress,0,sizeof(toBindAddress));
	toBindAddress.sun_family = AF_UNIX;
	strcpy(toBindAddress.sun_path,m_socketName.c_str());
	
	if ( bind(m_socketFileDescriptor, (const struct sockaddr*)&toBindAddress, SUN_LEN(&toBindAddress)) < 0 )
	{
		Close();
	}

	return (-1 != m_socketFileDescriptor );
}

bool CSocket::IsValid()
{
	return ( -1 != m_socketFileDescriptor );
}

void CSocket::Close()
{
	close(m_socketFileDescriptor);
	m_socketFileDescriptor = -1;
}

Int32 CSocket::Send(CSocketAddress& sockAddress, Int8* buffer, const Int32& bytestToSend)
{
	socklen_t addressFieldSize(SUN_LEN(sockAddress.GetAddressStructure()));
	return sendto(m_socketFileDescriptor, buffer, bytestToSend, 0, (struct sockaddr*)sockAddress.GetAddressStructure(), addressFieldSize );
}


Int32 CSocket::Receive(CSocketAddress& sockAddress, Int8* buffer, const Int32& bytesToSend)
{
	socklen_t addressFieldSize(sizeof(struct sockaddr_un));
	return recvfrom(m_socketFileDescriptor, buffer, bytesToSend, 0, (struct sockaddr*)sockAddress.GetAddressStructure(), &addressFieldSize );
}



}
