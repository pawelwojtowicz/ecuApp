#include "CMsgFactory.h"
#include "CMsgConfigurePID.h"
#include "CMsgSetAllMotors.h"
#include "CMsgSetCommMode.h"
#include "CMsgSetControlMode.h"

namespace RBCGateway
{
	
CMsgBase* CMsgFactory::CreateMessage(tStringVector arguments)
{
	CMsgBase* pMsgInstance = 0;
	size_t argumentCount( arguments.size() );
	if ( argumentCount > 0 )
	{
		std::string msgName( arguments[0]);
		
		if (msgName == "ConfigurePID")
		{
			pMsgInstance = new CMsgConfigurePID();
		}
		else if (msgName == "SetAllMotors")
		{
			pMsgInstance = new CMsgSetAllMotors();
		}
		else if (msgName == "SetCommMode")
		{
			pMsgInstance = new CMsgSetCommMode();
		}
		else if (msgName == "SetControlMode")
		{
			pMsgInstance = new CMsgSetControlMode();
		}	
	}
	
	return pMsgInstance;
}
	
};
