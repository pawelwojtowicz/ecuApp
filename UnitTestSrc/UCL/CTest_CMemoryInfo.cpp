#include <gtest/gtest.h>
#include <UCL/CMemoryInfo.h>

TEST(CMemoryInfo,Basic)
{
	UCL::CMemoryInfo memInfo;
	
  EXPECT_EQ(memInfo.IsValid(),true);
}


