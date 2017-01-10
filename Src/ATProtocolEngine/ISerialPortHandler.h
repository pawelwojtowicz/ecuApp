#pragma once
#include <Global/GlobalTypes.h>

namespace ATProtocolEngine
{
class ISerialPortHandler
{
public:
	ISerialPortHandler(){};
	virtual ~ISerialPortHandler(){};

	virtual bool OpenPort() = 0;
	virtual void ClosePort() = 0;

	virtual void StartProcessing() = 0;
	virtual void StopProcessing() = 0;

	virtual bool SendCommand( const std::string& serializeCommand ) = 0;

private:
	ISerialPortHandler(const ISerialPortHandler&);
	ISerialPortHandler& operator=(const ISerialPortHandler&);
};
}
