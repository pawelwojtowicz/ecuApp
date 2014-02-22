#include "CSerialPort.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

namespace UCL
{



  CSerialPort::CSerialPort()
    : m_portHandle(-1)
  {
  }

  CSerialPort::~CSerialPort()
  {
    if ( -1 != m_portHandle )
    {
      Close();
    }
  }


  bool CSerialPort::Open(const std::string& portName)
  {
    // portName - name of the port
    // O_RDWR   - we will read/write to the port
    // O_NOCTTY - prevent other inputs ( keyboard ) from influencing the port.
    // O_NDELAY - do not care if the device is really connected
    m_portHandle = open( portName.c_str(), O_RDWR | O_NOCTTY | O_NDELAY );
    

    return ( -1 != m_portHandle );
  }

  bool CSerialPort::Configure(const std::string& configurationString)
  {
    bool retVal(false);
    
    if ( -1 == m_portHandle )
    {
      struct termios portConfiguration;

      // get the current settings
      retVal = ( 0 == tcgetattr(m_portHandle,&portConfiguration) );

      // parse the configuration string, and fill in the termios structure suitable to new parameters
      retVal &= ParseConfigurationString( configurationString, portConfiguration );

      // apply the settings right away ( TCSANOW )
      // TCSADRAIN - would be - apply the settings after emptying the transmit buffer
      // TCSAFLUSH - flush the buffers and apply the changes.
      retVal &= ( 0 == tcsetattr(m_portHandle, TCSANOW ,&portConfiguration) );
    }
 


    return retVal;

  }

  void CSerialPort::Close()
  {
    close(m_portHandle);
    m_portHandle=-1;
  }

  Int32 CSerialPort::Read( Int8* rxBuffer, const Int32& bytesToRead )
  {
    Int32 bytesRead(-1);

    if ( -1 != m_portHandle )
    {
      bytesRead = read(m_portHandle, rxBuffer, bytesToRead );
    }

    return bytesRead;
  }


  Int32 CSerialPort::Write( Int8* txBuffer,const Int32& bytesToWrite )
  {
    Int32 bytesWritten(-1);

    if ( -1 != m_portHandle )
    {
      bytesWritten = write(m_portHandle, txBuffer, bytesToWrite );
    }
    
    return bytesWritten;
  }

  bool CSerialPort::ParseConfigurationString(const std::string& configurationString, struct termios& portConfig)
  {
    return true;
  }

  bool CSerialPort::WaitTxEmpty()
  {
    if ( -1 != m_portHandle )
    {
      return ( 0 == tcdrain(m_portHandle) );
    }
    
    return false;
  }

  bool CSerialPort::ClearRx()
  {
    if ( 0!= m_portHandle )
    {
      return ( 0 == tcflush(m_portHandle, TCIFLUSH) );
    }
    return false;
  }

  bool CSerialPort::ClearTx()
  {
    if ( 0 != m_portHandle )
    {
      return ( 0 == tcflush(m_portHandle, TCOFLUSH ) );
    }
    return false;
  }

}
