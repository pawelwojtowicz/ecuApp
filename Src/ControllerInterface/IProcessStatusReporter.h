#ifndef CONTROLLER_IPROCESSSTATUSREPORTER_H
#define CONTROLLER_IPROCESSSTATUSREPORTER_H
#include <GlobalTypes.h>
#include "ControllerTypes.h"

namespace Controller
{
class CPublicProcessInfo;

class IProcessStatusReporter
{
public:
	IProcessStatusReporter() {};
	virtual ~IProcessStatusReporter() {};
	
	virtual bool SendProcessStatus(const UInt32 processId, const tProcessStatus& status ) = 0;

	virtual bool PublishProcessInfo( CPublicProcessInfo& processInfo) = 0;


	
private:
	IProcessStatusReporter( const IProcessStatusReporter&);
	IProcessStatusReporter& operator=( const IProcessStatusReporter&);
};

}

#endif
