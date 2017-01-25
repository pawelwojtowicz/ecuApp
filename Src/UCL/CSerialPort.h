#ifndef UCL_CSERIALPORT_H
#define UCL_CSERIALPORT_H

#include <GlobalTypes.h>

struct termios;

namespace UCL
{
class CSerialPort
{
 public:

  CSerialPort();
  virtual ~CSerialPort();


  bool Open(const std::string& portName);
  bool Configure(const std::string& configurationString);
  void Close();

  bool IsValid() { return ( -1 != m_portHandle );};

  Int32 Read( Int8* rxBuffer, const Int32& bytesToRead );
  Int32 Write( const Int8* ttxBuffer,const Int32& bytesToWrite );

  bool WaitTxEmpty();
	bool WaitRxDataAvailable( UInt32 readTimeout );

  bool ClearRx();
  bool ClearTx();

#ifndef UNIT_TEST
 private:
#endif
  bool ParseConfigurationString( const std::string& configurationString, struct termios& portConfig);
  


 private:

  Int32 m_portHandle;

};

}


#endif
