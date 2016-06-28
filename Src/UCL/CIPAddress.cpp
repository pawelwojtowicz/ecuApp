#include "CIPAddress.h"
#include <sys/socket.h>
#include <arpa/inet.h>

namespace UCL
{

CIPAddress::CIPAddress( const std::string& ipString)
: m_address(0)
{
	struct in_addr ipAddr;
	inet_aton(ipString.c_str(), &ipAddr);
	m_address = ipAddr.s_addr;
}

CIPAddress::CIPAddress( const struct sockaddr_in& sockaddr)
: m_address(sockaddr.sin_addr.s_addr)
{
}

CIPAddress::CIPAddress( const in_addr& inAddr)
: m_address(inAddr.s_addr)
{
}

CIPAddress::CIPAddress( const CIPAddress& ipAddress)
: m_address(ipAddress.m_address)
{
}

CIPAddress& CIPAddress::operator=(const CIPAddress& ipAddress)
{
	this->m_address = ipAddress.m_address;
	return *this;
}

CIPAddress& CIPAddress::operator=(const struct sockaddr_in& sockaddr)
{
	this->m_address = sockaddr.sin_addr.s_addr;
	return *this;
}

CIPAddress& CIPAddress::operator=(const struct in_addr& inAddr)
{
	this->m_address = inAddr.s_addr;
	return *this;
}

CIPAddress::operator struct sockaddr_in() const
{
	struct sockaddr_in output;

	output.sin_family = AF_INET;
	output.sin_addr.s_addr = m_address;

	return output;
}

CIPAddress::operator struct in_addr() const
{
	struct in_addr output;
	output.s_addr = m_address;

	return output;
}

std::string CIPAddress::ToString() const
{
	struct in_addr ipAddr;
	ipAddr.s_addr = m_address;
	std::string output(inet_ntoa(ipAddr));

	return output;
}

bool CIPAddress::operator==(const CIPAddress& rhs) const
{
	return (m_address == rhs.m_address);
}

bool CIPAddress::operator<(const CIPAddress& rhs) const
{
	return (m_address < rhs.m_address);
}

bool CIPAddress::operator>(const CIPAddress& rhs) const
{
	return (m_address > rhs.m_address);
}


}
