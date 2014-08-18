#include "CSocket.h"
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

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
	
	if ( -1 != m_socketFileDescriptor )
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
	
	if ( bind(m_socketFileDescriptor, (const struct sockaddr*)&toBindAddress, sizeof(toBindAddress)) < 0 )
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

}
