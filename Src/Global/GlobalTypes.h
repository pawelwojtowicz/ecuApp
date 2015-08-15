#ifndef GLOBALTYPES_H
#define GLOBALTYPES_H
#include <stdint.h>
#include <list>
#include <vector>
#include <map>
#include <string>

typedef unsigned char 	UInt8;
typedef unsigned short 	UInt16;
typedef unsigned int 		UInt32;
typedef char						Int8;
typedef short						Int16;
typedef int							Int32;
typedef int64_t					Int64;
typedef uint64_t				UInt64;

typedef float						Real32;
typedef double					Real64;

typedef std::list<std::string> tStringList;
typedef std::vector<std::string> tStringVector;

/** the map, which enables the use of variableName, variableValue search containers */
typedef std::map<std::string, std::string> tVariablesMap;
typedef tVariablesMap::const_iterator tVariablesConstIter;
typedef tVariablesMap::iterator tVariablesIter;

static const std::string s_cEmptyString("");
#endif
