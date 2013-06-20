#include "CConfigNode.h"
#include "CParameter.h"
#include <stdio.h>
#include <UCL/CTokenizer.h>

namespace Configuration
{
void CConfigNode::AddConfigNode( const std::string& nodeName, CConfigNode* pConfigNode )
{
	m_configNodesMap.insert( tName2ConfigNodeMap::value_type( nodeName, pConfigNode) );
}

void CConfigNode::AddParameter( const std::string& parameterName, const std::string& type, const std::string& value )
{
	CParameter* pParameter = new CParameter( type, value );
	if ( 0 != pParameter )
	{
		if ( pParameter->IsValid() )
		{
			m_parametersMap.insert( tName2ParameterMap::value_type( parameterName, pParameter ) );
		}
		else
		{
			delete pParameter;
		}
	}
}

const CConfigNode* CConfigNode::GetConfigNode(const std::string& configNodeName) const
{
	char pathSeparators[] = {"."};
	UCL::CTokenizer configNodePath(configNodeName,pathSeparators);
	UInt32 indirectionLevel(configNodePath.GetTokenCount());

	const CConfigNode* pConfigNode = this;
	
	for (UInt32 i = 0 ; i < indirectionLevel && 0 != pConfigNode ; ++i )
	{
		tName2ConfigNodeConstIter nodeConstIter = pConfigNode->m_configNodesMap.find(configNodePath.GetToken(i));
		if ( m_configNodesMap.end() != nodeConstIter )
		{
			pConfigNode = nodeConstIter->second;
		}
		else
		{
			pConfigNode = 0;
		}
	}
	return pConfigNode;
}

const CParameter* CConfigNode::GetParameter( const std::string& parameterName ) const
{
	static CParameter emptyParameter;

	tName2ParameterConstIter pParamCIter = m_parametersMap.find(parameterName);

	if ( m_parametersMap.end()  != pParamCIter )
	{
		return pParamCIter->second;
	}
	return &emptyParameter;
}


}
