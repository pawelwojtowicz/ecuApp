#include "CUnixDomainSocket.h"
#include <stdio.h>
#include <errno.h>
#include <sys/ioctl.h>

namespace UCL
{

CUnixDomainSocket::CUnixDomainSocket()
: m_socketFileDescriptor(-1)
, m_socketName()
{
}

CUnixDomainSocket::~CUnixDomainSocket()
{
}
	
bool CUnixDomainSocket::Bind(const std::string& queueName)
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

bool CUnixDomainSocket::IsValid()
{
	return ( -1 != m_socketFileDescriptor );
}

void CUnixDomainSocket::Close()
{
	close(m_socketFileDescriptor);
	m_socketFileDescriptor = -1;
}

Int32 CUnixDomainSocket::Send(CSocketAddress& sockAddress, Int8* buffer, const Int32& bytestToSend)
{
	return sendto(m_socketFileDescriptor, buffer, bytestToSend, 0, (struct sockaddr*)sockAddress.GetAddressStructure(), sockAddress.GetAddressSize() );
}


Int32 CUnixDomainSocket::Receive(CSocketAddress& sockAddress, Int8* buffer, const Int32& bytesToSend)
{
	socklen_t addressFieldSize( sizeof(struct sockaddr_un) );
	return recvfrom(m_socketFileDescriptor, buffer, bytesToSend, 0, (struct sockaddr*)sockAddress.GetAddressStructure(), &addressFieldSize );
}

bool CUnixDomainSocket::IsEmpty()
{
	bool retVal(false);
	
	if ( m_socketFileDescriptor > 0 )
	{
		Int32 dataLength(0);
		ioctl(m_socketFileDescriptor, FIONREAD,&dataLength);
		retVal = ( dataLength == 0 );
	}
	
	return retVal;
}

}
