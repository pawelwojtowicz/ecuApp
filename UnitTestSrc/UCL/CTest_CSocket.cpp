#include <gtest/gtest.h>
#include <errno.h>
#include "UCL/CSocket.h"

std::string address("./testOfTheQueue");

TEST(CSocket,Basic_NonInitialized)
{ 
  UCL::CSocket socket;
  ASSERT_FALSE(socket.IsValid() );
}

TEST(CSocket,Basic_Bound)
{
  
  UCL::CSocket socket;
  socket.Bind(address);
  
  ASSERT_TRUE(socket.IsValid() );
  
  socket.Close();
	ASSERT_FALSE(socket.IsValid() );
}

TEST(CSocket,Basic_BoundAgain)
{
  UCL::CSocket socket;
  socket.Bind(address);
  ASSERT_TRUE(socket.IsValid() );
  
  socket.Close();
	
	socket.Bind(address);
	ASSERT_TRUE(socket.IsValid() );
  socket.Close();
}

TEST(CSocket,SendReceive)
{
  UCL::CSocket socket;
  socket.Bind(address);
  ASSERT_TRUE(socket.IsValid() );
  UCL::CSocketAddress testAddress(address);
  
  Int8 testInput1[] = {"TestInput1"};
  Int8 testInput2[] = {"TestInputTestInput2"};
  Int8 testInput1Size = sizeof(testInput1);
  Int8 testInput2Size = sizeof(testInput2);

	Int8 sentBytes(0);  
  
  sentBytes = socket.Send(testAddress, testInput1, testInput1Size);

	ASSERT_EQ(sentBytes,testInput1Size);

  sentBytes = socket.Send(testAddress, testInput2, testInput2Size);

	ASSERT_EQ(sentBytes,testInput2Size);

	Int8 output[100];
	Int8 receivedData(0);

  memset(output,0,100);
  receivedData = socket.Receive(testAddress,output,100);
	ASSERT_EQ(receivedData,testInput1Size);
	ASSERT_STREQ(output,testInput1);

  memset(output,0,100);
  receivedData = socket.Receive(testAddress,output,100);
	ASSERT_EQ(receivedData,testInput2Size);
	ASSERT_STREQ(output,testInput2);

  socket.Close();
}

TEST(CSocket,DetectEmptyBuffer)
{
  UCL::CSocket socket;
  socket.Bind(address);
  UCL::CSocketAddress testAddress(address);
  
  Int8 testInput1[] = {"TestInput1"};
  Int8 testInput2[] = {"TestInputTestInput2"};
  Int8 testInput1Size = sizeof(testInput1);
  Int8 testInput2Size = sizeof(testInput2);

	Int8 sentBytes(0);  
  
  sentBytes = socket.Send(testAddress, testInput1, testInput1Size);
  sentBytes = socket.Send(testAddress, testInput2, testInput2Size);

	ASSERT_EQ( false ,socket.IsEmpty() );

	Int8 output[100];
	
  memset(output,0,100);
  socket.Receive(testAddress,output,100);
	ASSERT_EQ( false ,socket.IsEmpty() );

  memset(output,0,100);
  socket.Receive(testAddress,output,100);
	ASSERT_EQ( true ,socket.IsEmpty() );

  socket.Close();
}


TEST(CSocketAddress,CopyConstructor)
{
	UCL::CSocketAddress address1("testAddress");
	UCL::CSocketAddress address2(address1);
	
	ASSERT_EQ(address1.GetAddressSize(), address2.GetAddressSize());
	ASSERT_STREQ(address1.GetAddressStructure()->sun_path, address2.GetAddressStructure()->sun_path);
}

TEST(CSocketAddress,AssignmentOperator)
{
	UCL::CSocketAddress address1("testAddress");
	UCL::CSocketAddress address2 = address1;

	ASSERT_EQ(address1.GetAddressSize(), address2.GetAddressSize());
	ASSERT_STREQ(address1.GetAddressStructure()->sun_path, address2.GetAddressStructure()->sun_path);
}

TEST(CSocketAddress,ComparisonOperator)
{
	UCL::CSocketAddress address1("testAddress");
	UCL::CSocketAddress address2("testAddress");
	UCL::CSocketAddress address3("otherTestAddress");
	ASSERT_EQ(address1==address2, true);
	ASSERT_EQ(address1==address3, false);

}
