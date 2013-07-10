#ifndef CONTROLLER_CONTROLLERTYPES_H
#define CONTROLLER_CONTROLLERTYPES_H
namespace Controller
{
typedef enum
{
	eStatus_None,	
	eStatus_Iddle,
	eStatus_Busy,
	eStatus_Error
} tProcessStatus;
}
#endif
