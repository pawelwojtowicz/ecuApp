#pragma once
#include <Global/GlobalTypes.h>

namespace ATProtocolEngine
{
class ISerialPortHandler
{
public:
	ISerialPortHandler(){};
	virtual ~ISerialPortHandler(){};

	virtual bool SendCommand( const std::string& serializeCommand ) = 0;

private:
	ISerialPortHandler(const ISerialPortHandler&);
	ISerialPortHandler& operator=(const ISerialPortHandler&);
};
}
