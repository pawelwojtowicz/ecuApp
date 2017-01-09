#pragma once
#include <Global/GlobalTypes.h>
#include "IGSMDaemonConfiguration.h"

namespace GSMDaemon
{
class CGSMDaemonConfiguration : public IGSMDaemonConfiguration
{
public:
	CGSMDaemonConfiguration();
	~CGSMDaemonConfiguration();

	bool Initialize();
};
}
