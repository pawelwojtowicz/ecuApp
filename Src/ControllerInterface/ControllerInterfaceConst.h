#ifndef CONTROLLER_CONTROLLERINTERFACECONST_H
#define CONTROLLER_CONTROLLERINTERFACECONST_H
#include <RuntimeConst.h>

namespace Controller
{
static char s_ControllerQueueName[]={"/ControllerQueue"};

typedef enum
{
	eStatus_Iddle,
	eStatus_Busy
} tProcessStatus;
}


#endif