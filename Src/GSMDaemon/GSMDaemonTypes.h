#pragma once
#include <Global/GlobalTypes.h>

namespace GSMDaemon
{
typedef enum
{
	gsmUnknownStatus			= 0x00,
	gsmOperatorAvailable 	= 0x01,
	gsmOperatorCurrent		= 0x02,
	gsmOperatorForbidden	= 0x03
} tOperatorStatus;

typedef enum
{
	gsmCModeAuto					= 0x00,
	gsmCModeManual				= 0x01,
	gsmCModeDeregister		= 0x02,
	gsmCModeSetFormat			= 0x03,
	gsmCModeManualAuto		= 0x04
} tOperatorConnectionMode;

typedef enum
{
	gsmNotRegistered 	= 0x00,
	gsmRegistered			= 0x01,
	gsmConnecting			= 0x02,
	gsmRegDenied			= 0x03,
	gsmUnknown				= 0x04,
	gsmRegRoaming			= 0x05
} tNetworkRegistrationState;

}
