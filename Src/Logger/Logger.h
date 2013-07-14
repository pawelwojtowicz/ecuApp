#ifndef LOGGER_LOGGER_H
#define LOGGER_LOGGER_H
#define ERROR 		1
#define WARNING 	2
#define INFO	 		4
#define DATA	 		8
#define DET1	 		16
#define DET2	 		32
#include "CLogMsg.h"

#define RETAILMSG( zone , logMsg)					 							\
	if ( 0 != Logger::CLogMsg::ZoneEnabled( zone ) ) 			\
	{																											\
		Logger::CLogMsg msg( zone, __FILE__, __LINE__);	\
		msg.LogText logMsg ;																\
	}																											\


#endif
