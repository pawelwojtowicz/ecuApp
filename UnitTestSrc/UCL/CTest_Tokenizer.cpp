#include <gtest/gtest.h>
#include <UCL/CTokenizer.h>

TEST(CTokenizer,Basic)
{
  std::string inputString("to|jest|test|superowy");
  UCL::CTokenizer tokenizer(inputString,"|");

  EXPECT_EQ(4,tokenizer.GetTokenCount());
}

TEST(CTokenizer,Detail)
{
  std::string inputString("aaaa1 bbbb2 cccc3 dddd4 ssss5");
  UCL::CTokenizer tokenizer(inputString," ");

  EXPECT_EQ(5, tokenizer.GetTokenCount());
  EXPECT_EQ("aaaa1",tokenizer.GetToken(0));
  EXPECT_EQ("bbbb2",tokenizer.GetToken(1));
  EXPECT_EQ("cccc3",tokenizer.GetToken(2));
  EXPECT_EQ("dddd4",tokenizer.GetToken(3));
  EXPECT_EQ("ssss5",tokenizer.GetToken(4));
}
