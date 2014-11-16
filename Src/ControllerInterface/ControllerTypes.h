#ifndef CONTROLLER_CONTROLLERTYPES_H
#define CONTROLLER_CONTROLLERTYPES_H
namespace Controller
{
typedef enum
{
	eStatus_None,	
	eStatus_Iddle,
	eStatus_Busy,
	eStatus_Error,
	eStatus_Stopped
} tProcessStatus;

typedef enum
{
	eSessionState_Iddle,
	eSessionState_Init1,
	eSessionState_Init2,
	eSessionState_Init3,
	eSessionState_Running,
	eSessionState_PendingShutdown,
	eSessionState_Shutdown,
	eSessionState_PowerOff
} tSessionState;
}
#endif
