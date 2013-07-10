#ifndef UCL_SYSTEMENVIRONMENT_H
#define UCL_SYSTEMENVIRONMENT_H
#include <string>

namespace UCL
{
class SystemEnvironment
{
public:
	typedef enum
	{
		Dir_App,
		Dir_Config,
		Dir_Log,
		Dir_Temp
	} tPathType;
	static const std::string GetVariable( const std::string& variableName );

	static bool SetVariable(const std::string& variableName, const std::string& variableValue );
	
	static bool UnsetVariable( const std::string& variableName );

	static bool ClearEnvironment();

	static std::string ResolveEnvironmentVariable(const std::string& inputString);

	static std::string ResolvePath(const tPathType&, const std::string& fileName);
};

}

#endif
