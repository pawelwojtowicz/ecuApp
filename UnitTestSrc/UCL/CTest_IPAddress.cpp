#include <gtest/gtest.h>
#include <UCL/CIPAddress.h>

TEST(CIPAddress,FromStringToSockAddrAndBack)
{
	std::string ipAddress("192.168.1.142");

	UCL::CIPAddress address(ipAddress);

	struct sockaddr_in ipStructure = address;

	UCL::CIPAddress address2(ipStructure);

	std::string outputIPString(address2.ToString());

  EXPECT_EQ(ipAddress,outputIPString);
}


