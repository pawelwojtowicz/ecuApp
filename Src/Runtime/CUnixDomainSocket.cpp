#include "CUnixDomainSocket.h"
#include <sys/socket.h>
#include <sys/un.h>

#include <stdio.h>
#include <errno.h>
#include <string.h>

namespace Runtime
{
CUnixDomainSocket::CUnixDomainSocket()
: m_socketfd(-1)
{
}

CUnixDomainSocket::~CUnixDomainSocket()
{
}

bool CUnixDomainSocket::InitializeServer( const std::string& ownQueueName )
{
	m_socketfd = socket( AF_UNIX, SOCK_DGRAM, 0 );
	
	if ( 0 > m_socketfd )
	{
		return false;
	}
	
	struct sockaddr_un serverAddress;
		
	// clear the structure
	memset(&serverAddress, 0 ,sizeof(serverAddress));
	
	// initialize the fields
	serverAddress.sun_family = AF_UNIX;		
	strcpy( serverAddress.sun_path, ownQueueName.c_str() );
	
	// unlink current linking
	unlink( ownQueueName.c_str() );

	if ( 0 > bind( m_socketfd, ( const struct sockaddr *)&serverAddress , sizeof(sockaddr_un) )))
	{
		close( m_socketfd );
		return false;
	}

  return true;
}

bool CUnixDomainSocket::ConnectToServer( const std::string& serverQueue )
{
	m_socketfd = socket( AF_UNIX, SOCK_DGRAM, 0 );
	
	if ( 0 > m_socketfd )
	{
		return false;
	}
	
	struct sockaddr_un serverAddress;
		
	// clear the structure
	memset(&serverAddress, 0 ,sizeof(serverAddress));
	
	// initialize the fields
	serverAddress.sun_family = AF_UNIX;		
	strcpy( serverAddress.sun_path, ownQueueName.c_str() );
	
	// unlink current linking
	unlink( ownQueueName.c_str() );

	if ( 0 > bind( m_socketfd, ( const struct sockaddr *)&serverAddress , sizeof(sockaddr_un) )))
	{
		close( m_socketfd );
		return false;
	}

  return true;


    return true;
}

void CUnixDomainSocket::Shutdown()
{
  close(m_socketfd);
}

bool CUnixDomainSocket::IsValid()
{
  return ( -1 != m_socketfd )
}
  
size_t CUnixDomainSocket::SendData( const Int8* buffer, size_t bufferSize)
{
}

size_t CUnixDomainSocket::ReceiveData( Int8* buffer, size_t bufferSize )
{
}

}
