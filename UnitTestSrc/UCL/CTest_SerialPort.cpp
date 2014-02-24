#include <gtest/gtest.h>
#include <UCL/CSerialPort.h>

TEST(SerialPort,Opening)
{
  UCL::CSerialPort port;
  EXPECT_EQ(false, port.Open("COM1:"));
}
