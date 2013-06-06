#ifndef CONFIGURATION_CONFIGURATIONCONST_H
#define CONFIGURATION_CONFIGURATIONCONST_H

#include <GlobalTypes.h>
#include <map>

namespace Configuration
{

static char sConst_ConfigurationMainNode[] 			= "Configuration";
static char sConst_ConfigurationNode[] 					= "CNode";
static char sConst_ConfigurationParameter[] 		= "Parameter";
static char sConst_ConfigurationTag_KeyName[]		= "Name";
static char sConst_ConfigurationTag_Type[]			= "Type";

static char sConst_ParamType_UInt8[]						= "UInt8";
static char sConst_ParamType_UInt16[]						= "UInt16";
static char sConst_ParamType_UInt32[]						= "UInt32";

static char sConst_ParamType_Int8[]							= "Int8";
static char sConst_ParamType_Int16[]						= "Int16";
static char sConst_ParamType_Int32[]						= "Int32";

static char sConst_ParamType_Real32[]						= "Real32";
static char sConst_ParamType_Real64[]						= "Real64";

static char sConst_ParamType_String[]						= "String";
}
#endif
