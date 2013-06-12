#ifndef UCL_SYSTEMENVIRONMENT_H
#define UCL_SYSTEMENVIRONMENT_H
#include <string>

namespace UCL
{
class SystemEnvironment
{
public:
	static const std::string GetVariable(const std::string& variableName);

	static bool SetVariable(const std::string& variableName, const std::string& variableValue );
	
	static bool UnsetVariable( const std::string& variableName );

	static bool ClearEnvironment();

	static std::string ResolveEnvironmentVariable(const std::string& inputString);
};

}

#endif
