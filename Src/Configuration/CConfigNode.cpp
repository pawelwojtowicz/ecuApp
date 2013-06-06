#include "CConfigNode.h"
#include <stdio.h>

namespace Configuration
{
void CConfigNode::AddConfigNode( const std::string& nodeName, CConfigNode* pConfigNode )
{
	m_configNodesMap.insert( tName2ConfigNodeMap::value_type( nodeName, pConfigNode) );
}

void CConfigNode::AddParameter( const std::string& parameterName, const std::string& type, const std::string& value )
{
	printf("Dodajemy parametr %s, %s, %s\n", parameterName.c_str(), type.c_str(),value.c_str() );
}

}
