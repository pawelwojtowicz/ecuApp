#include "CParameterBundle.h"

namespace ATProtocolEngine
{

CParameterBundle::CParameterBundle()
{
}

CParameterBundle::~CParameterBundle()
{
}

void CParameterBundle::Store(const std::string& paramName, const std::string& paramValue)
{
	m_parametersMap[paramName] = paramValue;
}
	
bool CParameterBundle::IsAvailable( const std::string& paramName) const
{
	return ( m_parametersMap.end() != m_parametersMap.find(paramName) );
}

const std::string& CParameterBundle::GetParameter(const std::string& paramName) const
{
	tParameterIterator pCIter( m_parametersMap.find(paramName) );
	if ( m_parametersMap.end() != pCIter )
	{
		return pCIter->second;
	}

	static const std::string emptyString("");
	return emptyString;
}

void CParameterBundle::ResetBundle()
{
	m_parametersMap.clear();
}

void CParameterBundle::Reset( const std::string& paramName )
{
	m_parametersMap.erase( paramName );
}

}
