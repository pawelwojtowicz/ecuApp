#pragma once
#include <Global/GlobalTypes.h>

namespace GSMDaemon
{
class IModemListener
{
public:
	IModemListener() {};
	virtual ~IModemListener() {};

private:
	IModemListener(const IModemListener&);
	IModemListener& operator=(const IModemListener&);
};
}
