#ifndef CONTROLLER_ICONTROLLERSERVICES_H
#define CONTROLLER_ICONTROLLERSERVICES_H
#include "ControllerInterfaceConst.h"

namespace Controller
{
class IControllerServices
{
public:
	IControllerServices(){};
	virtual ~IControllerServices(){};

	virtual void NotifyUnitInitialized(	const UInt32& unitId, 
																			const std::string& processQueue, 
																			const std::string& unitVersion) = 0;
	virtual void NotifyUnitHeartbeat(	const UInt32 unitId, 
																		const tProcessStatus& status ) = 0;

	virtual void NotifyShutdownRequest() = 0;
	virtual void NotifyRestartRequest() = 0;

private:
	IControllerServices(const IControllerServices&);
	IControllerServices& operator=(const IControllerServices&);
};

}
#endif
