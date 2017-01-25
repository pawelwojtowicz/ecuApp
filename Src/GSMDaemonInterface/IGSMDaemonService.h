#pragma once
#include <Global/GlobalTypes.h>

namespace GSMDaemon
{
class IGSMDaemonService
{
public:
	IGSMDaemonService() {};
	virtual ~IGSMDaemonService() {};
	
	virtual void NotifyATResponseReceived( const std::string& response ) = 0;
	virtual void NotifyATPromptReceived( const std::string& prompt ) = 0; 

private:
	IGSMDaemonService(const IGSMDaemonService&);
	IGSMDaemonService& operator=(const IGSMDaemonService&);
};
}
