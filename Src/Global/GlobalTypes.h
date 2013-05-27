#ifndef GLOBALTYPES_H
#define GLOBALTYPES_H
#include <list>
#include <vector>
#include <string>

typedef unsigned char 	UInt8;
typedef unsigned short 	UInt16;
typedef unsigned int 		UInt32;
typedef char						Int8;
typedef short						Int16;
typedef int							Int32;

typedef float						Real32;
typedef double					Real64;

typedef std::list<std::string> tStringList;
typedef std::vector<std::string> tStringVector;

static const std::string s_cEmptyString("");
#endif
