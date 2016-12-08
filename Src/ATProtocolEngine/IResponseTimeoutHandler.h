#pragma once
#include <Global/GlobalTypes.h>

namespace ATProtocolEngine
{
class IResponseTimeoutHandler
{
public:
	IResponseTimeoutHandler() {};
	virtual ~IResponseTimeoutHandler() {};

	virtual void StartTimeout( UInt32 timeout ) = 0;
	virtual void StopTimeout() = 0;

private:
	IResponseTimeoutHandler(const IResponseTimeoutHandler&);
	IResponseTimeoutHandler& operator=(const IResponseTimeoutHandler&);
};
}
