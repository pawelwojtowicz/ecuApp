#pragma once
#include <Global/GlobalTypes.h>

namespace ATProtocolEngine
{
class CParameterBundle
{
	typedef std::map<std::string, std::string> tParametersMap;
	typedef tParametersMap::const_iterator tParameterIterator;
public:
	CParameterBundle();
	~CParameterBundle();

	void Store(const std::string& paramName, const std::string& paramValue);
	
	bool IsAvailable( const std::string& paramName);

	const std::string& GetParameter(const std::string& paramName);

	void ResetBundle();

private:
	tParametersMap m_parametersMap;

};
}
