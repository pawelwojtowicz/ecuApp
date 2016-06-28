#ifndef UCL_CIPADDRESS_H
#define UCL_CIPADDRESS_H
#include <string>
#include <netinet/in.h>

namespace UCL
{
class CIPAddress
{
public:
	CIPAddress( const std::string& ipString);
	CIPAddress( const struct sockaddr_in& sockaddr);
	CIPAddress( const struct in_addr& inAddr);
	CIPAddress( const CIPAddress& ipAddress);

	CIPAddress& operator=(const CIPAddress& ipAddress);
	CIPAddress& operator=(const struct sockaddr_in& sockaddr);
	CIPAddress& operator=(const struct in_addr& inAddr);
	
	operator struct sockaddr_in() const;
	operator struct in_addr() const;

	bool operator==(const CIPAddress& rhs) const;
	bool operator<(const CIPAddress& rhs) const;
	bool operator>(const CIPAddress& rhs) const;


	std::string ToString() const;

private:
	unsigned long m_address;
	
};
}
#endif
