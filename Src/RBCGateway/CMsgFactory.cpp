#include "CMsgFactory.h"
#include "CMsgConfigurePID.h"
#include "CMsgSetAllMotors.h"
#include "CMsgSetCommMode.h"
#include "CMsgSetControlMode.h"
#include <stdio.h>
#include <stdlib.h>

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
			if (2 == arguments.size())
			{
				CMsgConfigurePID* pconfigurePID = new CMsgConfigurePID();
				
				pconfigurePID->SetAddress(static_cast<tModuleAddress>(atoi(arguments[1].c_str())));
				pconfigurePID->SetMotorID(atoi(arguments[2].c_str()));
				pconfigurePID->SetControlMode(static_cast<tControlMode>(atoi(arguments[3].c_str())));
				pconfigurePID->SetPIDGainType( static_cast<tControlPIDGainType>(atoi(arguments[4].c_str())) );
				pconfigurePID->SetPIDGain(atoi(arguments[5].c_str()));	
			
				pMsgInstance = pconfigurePID;
			}
		}
		else if (msgName == "SetAllMotors")
		{
			CMsgSetAllMotors* pSetAllMotors = new CMsgSetAllMotors();
			
			pMsgInstance = pSetAllMotors;
		}
		else if (msgName == "SetCommMode")
		{
			if ( 2 == arguments.size() )
			{
				CMsgSetCommMode* pSetCommMode = new CMsgSetCommMode();
				
				pSetCommMode->SetCommunicationMode(static_cast<tCommunicationMode>(atoi(arguments[1].c_str())));
			
				pMsgInstance = pSetCommMode;
			}
		}
		else if (msgName == "SetControlMode")
		{
			if (4 == arguments.size() )
			{
				CMsgSetControlMode* pSetControlMode = new CMsgSetControlMode();
				
				pSetControlMode->SetAddress(static_cast<tModuleAddress>(atoi(arguments[1].c_str())));
				pSetControlMode->SetMotorID(atoi(arguments[2].c_str()));
				pSetControlMode->SetControlMode(static_cast<tControlMode>(atoi(arguments[3].c_str())));
				pMsgInstance = pSetControlMode;
			}
		}	
	}
	
	return pMsgInstance;
}
	
};
