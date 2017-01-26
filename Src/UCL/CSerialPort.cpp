#include "CSerialPort.h"
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>
#include "CTokenizer.h"
#include <stdio.h>
#include <Logger/Logger.h>
#include <errno.h>
#include <string.h>

static const char s_constParamName_baud[]     = {"baud"};
static const char s_constParamName_data[]     = {"data"};
static const char s_constParamName_parity[]   = {"parity"};
static const char s_constParamName_stopBit[]  = {"stop"};

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
    
    if ( -1 != m_portHandle )
    {
      struct termios portConfiguration;

      // get the current settings
      retVal = ( 0 == tcgetattr(m_portHandle,&portConfiguration) );
      //RETAILMSG(INFO, ("GetAttr = %d", retVal));

      // parse the configuration string, and fill in the termios structure suitable to new parameters
      retVal &= ParseConfigurationString( configurationString, portConfiguration );
      //RETAILMSG(INFO, ("Parse Configs = %d", retVal));

      // apply the settings right away ( TCSANOW )
      // TCSADRAIN - would be - apply the settings after emptying the transmit buffer
      // TCSAFLUSH - flush the buffers and apply the changes.
      retVal &= ( 0 == tcsetattr(m_portHandle, TCSANOW ,&portConfiguration) );
      //RETAILMSG(INFO, ("SetAttr = %d", retVal));
      if ( !retVal )
      {
      	//RETAILMSG(INFO, ("Step final = [%s]", strerror(errno)));
      }
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


  Int32 CSerialPort::Write( const Int8* txBuffer,const Int32& bytesToWrite )
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
    bool retVal(false);
    long baudConstant(B9600);
    long data(CS8);
    long parity(0);
    long stop(0);

    CTokenizer configurationTokens(configurationString, " ");

    const UInt16 paramCount(configurationTokens.GetTokenCount());
    retVal = ( 0 != paramCount );

    for( UInt16 i = 0 ; paramCount > i && retVal ; i++ )
    {
      CTokenizer paramPair(configurationTokens.GetToken(i), "=");
      if ( 2 == paramPair.GetTokenCount() )
      {
	      std::string paramName = paramPair.GetToken(0);
	      std::string paramValue = paramPair.GetToken(1);
	      if ( s_constParamName_baud == paramName )
	      {
	        Int32 baudRate(atoi( paramValue.c_str() ) );
	        switch(baudRate)
	        {
	        case 115200:
	          baudConstant = B115200;
	          break;
          case 57600:
            baudConstant = B57600;
            break;
	        case 38400:
	          baudConstant = B38400;
	          break;
	        case 19200:
	          baudConstant = B19200;
	          break;
	        case 9600:
	          baudConstant = B9600;
            break;
	        case 4800:
	          baudConstant = B4800;
	          break;
	        case 2400:
	          baudConstant = B2400;
	          break;
	        case 1200:
	          baudConstant = B1200;
	          break;
	        case 600:
	          baudConstant = B600;
	          break;
	        case 300:
	          baudConstant = B300;
	          break;
	        default:
            retVal = false;
	        }
    	  }
	      else if ( s_constParamName_data == paramName )
	      {
          Int32 dataBits(atoi(paramValue.c_str()));
          switch ( dataBits )
          {
          case 5:
            data = CS5;
            break;
          case 6:
            data = CS6;
            break;
          case 7:
            data = CS7;
            break;
          case 8:
            data = CS8;
            break;
          default:
            retVal = false;
          }

	      }
        else if ( s_constParamName_parity == paramName )
        {
          if ( paramValue == "none" )
          {
            parity = 0;
          } 
          else if ( paramValue == "odd" )
          {
            parity = PARENB | PARODD ;
          }
          else if ( paramValue == "even" )
          {
            parity = PARENB ;
          }
          else
          {
            retVal = false;
          }
        }
        else if ( s_constParamName_stopBit == paramName )
        {
          Int32 stopBits( atoi(paramValue.c_str() ) );
          switch ( stopBits )
          {
          case 2:
            stop = CSTOPB;
            break;
          case 1:
            stop = 0;
            break;
          default:
            retVal = false;
          }
        }
	      else 
	      {
          // incorrect name of the parameter - return false
	        retVal = false ;
	      }
      }
      else
      {
        // at least one parameter has an incorrect format ( no '=' character between name and value )
        retVal = false;
      }
    }

    if ( retVal )
    {
      portConfig.c_cflag = data | stop | parity | baudConstant | CLOCAL | CREAD ;
			portConfig.c_iflag &= ~(INLCR | ICRNL | IGNCR);
    }
    return retVal;
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

	bool CSerialPort::WaitRxDataAvailable( UInt32 readTimeout )
	{
		fd_set inputSet;
		
		FD_ZERO(&inputSet);
		FD_SET(m_portHandle,&inputSet);

		struct timeval timeoutStructure;
		timeoutStructure.tv_sec = readTimeout;
		timeoutStructure.tv_usec = 0;

		return ( 0 < select(m_portHandle+1, &inputSet,NULL, NULL, &timeoutStructure ) );
	}


}
