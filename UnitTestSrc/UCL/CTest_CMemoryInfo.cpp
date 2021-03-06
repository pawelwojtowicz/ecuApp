#include <gtest/gtest.h>
#include <UCL/CMemoryInfo.h>

TEST(CMemoryInfo,Basic)
{
	UCL::CMemoryInfo memInfo;
	
  EXPECT_EQ(memInfo.IsValid(),true);
}

TEST(CMemoryInfo,GetValue)
{
	UCL::CMemoryInfo memInfo;
	
	Int32 info(0);
	
  EXPECT_EQ(memInfo.GetMemoryInfo(UCL::MemTotal)!=0, true);
}

