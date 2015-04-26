#ifndef RBCGATEWAY_RBCTYPES_H
#define RBCGATEWAY_RBCTYPES_H
#include <GlobalTypes.h>

namespace RBCGateway
{

typedef enum
{
	moduleIO					= 0x13,
	moduleHUB					= 0x11,
	moduleDrive				= 0x12,
	moduleStepping_1	= 0x13,
	moduleLeveling		= 0x14,
	moduleStepping_2	= 0x15
} tModuleAddress;

typedef enum
{
	cmdSetSpeed 				= 0x20,
	cmdSetPosition 			= 0x21,
	cmdSetMotorSpeed 		= 0x26,
	cmdSetMororPosition = 0x27,
	cmdSetIO						= 0x28,
	cmdSetAllMotors			= 0x2A,
	cmdSetCommMode			= 0x30,
	cmdSetControlMode		= 0x50,
	cmdConfigurePID			= 0x52,
	cmdResetEncoders		= 0x53,
	cmdGetState					= 0x6F,
	cmdGetConfiguration	= 0x70
} tCommandCodes;

typedef enum
{
	legid_LeftFront 	= 0x00,
	legid_RightFront	= 0x01,
	legid_LeftRear		= 0x02,
	legid_RightRear		= 0x03
}	tLegId;

typedef enum
{
	mode_Transparent	= 0x00,
	mode_Stream				= 0x01
} tCommunicationMode;
}
#endif
