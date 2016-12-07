#pragma once
#include <Global/GlobalTypes.h>
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

	virtual ISerializationEngine& GetSerializationEngine() = 0;

	virtual ISerialPortHandler& GetSerialPortHandler() = 0;

	virtual CParameterBundle& GetParameterBundle() = 0;
	
private:
	IActionExecutionContext(const IActionExecutionContext&);
	IActionExecutionContext& operator=(const IActionExecutionContext&);
};
}
