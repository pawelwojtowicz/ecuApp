#include "SystemEnvironment.h"
#include <stdlib.h>

namespace UCL
{
const std::string SystemEnvironment::GetVariable(const std::string& variableName)
{
	return std::string( getenv(variableName.c_str() ) );
}

bool SystemEnvironment::SetVariable(const std::string& variableName, const std::string& variableValue )
{
	return ( 0 == setenv(variableName.c_str() , variableValue.c_str() , 1) );
}
	
bool SystemEnvironment::UnsetVariable( const std::string& variableName )
{
	return ( 0 == unsetenv(variableName.c_str() ) );
}

bool SystemEnvironment::ClearEnvironment()
{
	return ( 0 == clearenv() );
}

}

