#pragma once
#include <Global/GlobalTypes.h>
#include <CSM/IActionFactory.h>
#include "IResponseTimeoutHandler.h"
#include "ISerializationEngine.h"
#include "ISerialPortHandler.h"
#include "CParameterBundle.h"

namespace ATProtocolEngine
{
class IActionExecutionContext
{
public:
	IActionExecutionContext() {};
	virtual ~IActionExecutionContext() {};

	virtual IResponseTimeoutHandler& GetTimeoutHandler() = 0;

	virtual ISerializationEngine& GetSerializationEngine() = 0;

	virtual ISerialPortHandler& GetSerialPortHandler() = 0;

	virtual CParameterBundle& GetParameterBundle() = 0;

	virtual void DispatchEvent( const std::string& eventName ) = 0;
	
private:
	IActionExecutionContext(const IActionExecutionContext&);
	IActionExecutionContext& operator=(const IActionExecutionContext&);
};
}
