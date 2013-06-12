#include "SystemEnvironment.h"
#include <stdlib.h>
#include <stdio.h>

#define VARIABLE_PREFIX "${"
#define VARIABLE_PREFIX_LENGTH 2
#define VARIABLE_POSTFIX "}"
#define VARIABLE_POSTFIX_LENGTH 1

namespace UCL
{
const std::string SystemEnvironment::GetVariable(const std::string& variableName)
{
	const char* variableString = getenv(variableName.c_str() ); 
	if ( 0 != variableString )
	{
		return std::string( getenv(variableName.c_str() ) );
	}

	return std::string();
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

std::string SystemEnvironment::ResolveEnvironmentVariable(const std::string& inputString)
{
	std::string output(inputString);
	size_t variablePosition(0);


	while ( variablePosition != std::string::npos )
	{
		variablePosition = output.find(VARIABLE_PREFIX, variablePosition );
		if (variablePosition != std::string::npos)
		{
			size_t variableEnd = output.find(VARIABLE_POSTFIX, variablePosition);
			if ( variableEnd != std::string::npos )
			{
				if ( ( variableEnd - variablePosition ) > VARIABLE_PREFIX_LENGTH )
				{
					// extract the name of the variable
					std::string variableName(output, variablePosition+VARIABLE_PREFIX_LENGTH , (variableEnd - variablePosition - VARIABLE_PREFIX_LENGTH ) );
					// replace the variable string with the environment variables.
					output.replace(variablePosition, (variableEnd - variablePosition + VARIABLE_POSTFIX_LENGTH), GetVariable(variableName));
				}
				else
				{
					variablePosition+=VARIABLE_PREFIX_LENGTH;
				}
			}
		}
	}
	return output;

	
}


}

