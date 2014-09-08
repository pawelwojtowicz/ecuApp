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



