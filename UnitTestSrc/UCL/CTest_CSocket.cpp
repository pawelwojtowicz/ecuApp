#include <gtest/gtest.h>
#include <errno.h>
#include "UCL/CSocket.h"

std::string address("#testOfTheQueue");

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
  
  socket.Close();
	
	socket.Bind(address);
	ASSERT_TRUE(socket.IsValid() );
  socket.Close();
}



