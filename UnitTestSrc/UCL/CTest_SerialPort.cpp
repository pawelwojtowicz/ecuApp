#include <gtest/gtest.h>
#include <UCL/CSerialPort.h>
#include <termios.h>

TEST(SerialPort,Configure_INV_8_none_2)
{
  UCL::CSerialPort port;
  struct termios settingsStructure;

  EXPECT_EQ(false, port.ParseConfigurationString("baud=15200 data=8 parity=none stop=2", settingsStructure) );
}

TEST(SerialPort,Configure_115200_8_none_2)
{
  UCL::CSerialPort port;
  struct termios settingsStructure;

  EXPECT_EQ(true, port.ParseConfigurationString("baud=115200 data=8 parity=none stop=2", settingsStructure) );
  EXPECT_EQ( B115200  , settingsStructure.c_cflag & CBAUD );
  EXPECT_EQ( CS8      , settingsStructure.c_cflag & CSIZE );
  EXPECT_EQ( CSTOPB   , settingsStructure.c_cflag & CSTOPB);
  EXPECT_EQ( 0        , settingsStructure.c_cflag & ( PARENB | PARODD ) );
}

TEST(SerialPort,Configure_57600_8_none_2)
{
  UCL::CSerialPort port;
  struct termios settingsStructure;

  EXPECT_EQ(true, port.ParseConfigurationString("baud=57600 data=8 parity=none stop=2", settingsStructure) );
  EXPECT_EQ( B57600   , settingsStructure.c_cflag & CBAUD );
  EXPECT_EQ( CS8      , settingsStructure.c_cflag & CSIZE );
  EXPECT_EQ( CSTOPB   , settingsStructure.c_cflag & CSTOPB);
  EXPECT_EQ( 0        , settingsStructure.c_cflag & ( PARENB | PARODD ) );
}

TEST(SerialPort,Configure_38400_8_none_2)
{
  UCL::CSerialPort port;
  struct termios settingsStructure;

  EXPECT_EQ(true, port.ParseConfigurationString("baud=38400 data=8 parity=none stop=2", settingsStructure) );
  EXPECT_EQ( B38400   , settingsStructure.c_cflag & CBAUD );
  EXPECT_EQ( CS8      , settingsStructure.c_cflag & CSIZE );
  EXPECT_EQ( CSTOPB   , settingsStructure.c_cflag & CSTOPB);
  EXPECT_EQ( 0        , settingsStructure.c_cflag & ( PARENB | PARODD ) );
}

TEST(SerialPort,Configure_19200_8_none_2)
{
  UCL::CSerialPort port;
  struct termios settingsStructure;

  EXPECT_EQ(true, port.ParseConfigurationString("baud=19200 data=8 parity=none stop=2", settingsStructure) );
  EXPECT_EQ( B19200   , settingsStructure.c_cflag & CBAUD );
  EXPECT_EQ( CS8      , settingsStructure.c_cflag & CSIZE );
  EXPECT_EQ( CSTOPB   , settingsStructure.c_cflag & CSTOPB);
  EXPECT_EQ( 0        , settingsStructure.c_cflag & ( PARENB | PARODD ) );
}

TEST(SerialPort,Configure_9600_8_none_2)
{
  UCL::CSerialPort port;
  struct termios settingsStructure;

  EXPECT_EQ(true, port.ParseConfigurationString("baud=9600 data=8 parity=none stop=2", settingsStructure) );
  EXPECT_EQ( B9600   , settingsStructure.c_cflag & CBAUD );
  EXPECT_EQ( CS8      , settingsStructure.c_cflag & CSIZE );
  EXPECT_EQ( CSTOPB   , settingsStructure.c_cflag & CSTOPB);
  EXPECT_EQ( 0        , settingsStructure.c_cflag & ( PARENB | PARODD ) );
}

TEST(SerialPort,Configure_4800_8_none_2)
{
  UCL::CSerialPort port;
  struct termios settingsStructure;

  EXPECT_EQ(true, port.ParseConfigurationString("baud=4800 data=8 parity=none stop=2", settingsStructure) );
  EXPECT_EQ( B4800   , settingsStructure.c_cflag & CBAUD );
  EXPECT_EQ( CS8      , settingsStructure.c_cflag & CSIZE );
  EXPECT_EQ( CSTOPB   , settingsStructure.c_cflag & CSTOPB);
  EXPECT_EQ( 0        , settingsStructure.c_cflag & ( PARENB | PARODD ) );
}

TEST(SerialPort,Configure_2400_8_none_2)
{
  UCL::CSerialPort port;
  struct termios settingsStructure;

  EXPECT_EQ(true, port.ParseConfigurationString("baud=2400 data=8 parity=none stop=2", settingsStructure) );
  EXPECT_EQ( B2400    , settingsStructure.c_cflag & CBAUD );
  EXPECT_EQ( CS8      , settingsStructure.c_cflag & CSIZE );
  EXPECT_EQ( CSTOPB   , settingsStructure.c_cflag & CSTOPB);
  EXPECT_EQ( 0        , settingsStructure.c_cflag & ( PARENB | PARODD ) );
}

TEST(SerialPort,Configure_1200_8_none_2)
{
  UCL::CSerialPort port;
  struct termios settingsStructure;

  EXPECT_EQ(true, port.ParseConfigurationString("baud=1200 data=8 parity=none stop=2", settingsStructure) );
  EXPECT_EQ( B1200    , settingsStructure.c_cflag & CBAUD );
  EXPECT_EQ( CS8      , settingsStructure.c_cflag & CSIZE );
  EXPECT_EQ( CSTOPB   , settingsStructure.c_cflag & CSTOPB);
  EXPECT_EQ( 0        , settingsStructure.c_cflag & ( PARENB | PARODD ) );
}

TEST(SerialPort,Configure_600_8_none_2)
{
  UCL::CSerialPort port;
  struct termios settingsStructure;

  EXPECT_EQ(true, port.ParseConfigurationString("baud=600 data=8 parity=none stop=2", settingsStructure) );
  EXPECT_EQ( B600    , settingsStructure.c_cflag & CBAUD );
  EXPECT_EQ( CS8      , settingsStructure.c_cflag & CSIZE );
  EXPECT_EQ( CSTOPB   , settingsStructure.c_cflag & CSTOPB);
  EXPECT_EQ( 0        , settingsStructure.c_cflag & ( PARENB | PARODD ) );
}

TEST(SerialPort,Configure_300_8_none_2)
{
  UCL::CSerialPort port;
  struct termios settingsStructure;

  EXPECT_EQ(true, port.ParseConfigurationString("baud=300 data=8 parity=none stop=2", settingsStructure) );
  EXPECT_EQ( B300    , settingsStructure.c_cflag & CBAUD );
  EXPECT_EQ( CS8      , settingsStructure.c_cflag & CSIZE );
  EXPECT_EQ( CSTOPB   , settingsStructure.c_cflag & CSTOPB);
  EXPECT_EQ( 0        , settingsStructure.c_cflag & ( PARENB | PARODD ) );
}

TEST(SerialPort,Configure_4800_7_none_2)
{
  UCL::CSerialPort port;
  struct termios settingsStructure;

  EXPECT_EQ(true, port.ParseConfigurationString("baud=4800 data=7 parity=none stop=2", settingsStructure) );
  EXPECT_EQ( B4800   , settingsStructure.c_cflag & CBAUD );
  EXPECT_EQ( CS7      , settingsStructure.c_cflag & CSIZE );
  EXPECT_EQ( CSTOPB   , settingsStructure.c_cflag & CSTOPB);
  EXPECT_EQ( 0        , settingsStructure.c_cflag & ( PARENB | PARODD ) );
}

TEST(SerialPort,Configure_4800_6_none_2)
{
  UCL::CSerialPort port;
  struct termios settingsStructure;

  EXPECT_EQ(true, port.ParseConfigurationString("baud=4800 data=6 parity=none stop=2", settingsStructure) );
  EXPECT_EQ( B4800   , settingsStructure.c_cflag & CBAUD );
  EXPECT_EQ( CS6      , settingsStructure.c_cflag & CSIZE );
  EXPECT_EQ( CSTOPB   , settingsStructure.c_cflag & CSTOPB);
  EXPECT_EQ( 0        , settingsStructure.c_cflag & ( PARENB | PARODD ) );
}

TEST(SerialPort,Configure_4800_5_none_2)
{
  UCL::CSerialPort port;
  struct termios settingsStructure;

  EXPECT_EQ(true, port.ParseConfigurationString("baud=4800 data=5 parity=none stop=2", settingsStructure) );
  EXPECT_EQ( B4800   , settingsStructure.c_cflag & CBAUD );
  EXPECT_EQ( CS5      , settingsStructure.c_cflag & CSIZE );
  EXPECT_EQ( CSTOPB   , settingsStructure.c_cflag & CSTOPB);
  EXPECT_EQ( 0        , settingsStructure.c_cflag & ( PARENB | PARODD ) );
}

TEST(SerialPort,Configure_4800_INV_none_2)
{
  UCL::CSerialPort port;
  struct termios settingsStructure;

  EXPECT_EQ(false, port.ParseConfigurationString("baud=4800 data=4 parity=none stop=2", settingsStructure) );
}

TEST(SerialPort,Configure_4800_8_odd_2)
{
  UCL::CSerialPort port;
  struct termios settingsStructure;

  EXPECT_EQ(true, port.ParseConfigurationString("baud=4800 data=5 parity=odd stop=2", settingsStructure) );
  EXPECT_EQ( B4800            , settingsStructure.c_cflag & CBAUD );
  EXPECT_EQ( CS5              , settingsStructure.c_cflag & CSIZE );
  EXPECT_EQ( CSTOPB           , settingsStructure.c_cflag & CSTOPB);
  EXPECT_EQ( (PARENB|PARODD)  , settingsStructure.c_cflag & ( PARENB | PARODD ) );
}

TEST(SerialPort,Configure_4800_8_even_2)
{
  UCL::CSerialPort port;
  struct termios settingsStructure;

  EXPECT_EQ(true, port.ParseConfigurationString("baud=4800 data=5 parity=even stop=2", settingsStructure) );
  EXPECT_EQ( B4800            , settingsStructure.c_cflag & CBAUD );
  EXPECT_EQ( CS5              , settingsStructure.c_cflag & CSIZE );
  EXPECT_EQ( CSTOPB           , settingsStructure.c_cflag & CSTOPB);
  EXPECT_EQ( (PARENB)         , settingsStructure.c_cflag & ( PARENB | PARODD ) );
}

TEST(SerialPort,Configure_4800_5_none_1)
{
  UCL::CSerialPort port;
  struct termios settingsStructure;

  EXPECT_EQ(true, port.ParseConfigurationString("baud=4800 data=5 parity=none stop=1", settingsStructure) );
  EXPECT_EQ( B4800      , settingsStructure.c_cflag & CBAUD );
  EXPECT_EQ( CS5        , settingsStructure.c_cflag & CSIZE );
  EXPECT_EQ( 0          , settingsStructure.c_cflag & CSTOPB);
  EXPECT_EQ( 0          , settingsStructure.c_cflag & ( PARENB | PARODD ) );
}

