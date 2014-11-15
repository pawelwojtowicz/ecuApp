#include "CConfiguration.h"
#include "CConfigNode.h"
#include "ConfigurationConst.h"
#include <XMLParser/xmlParser.h>
#include <stdio.h>

namespace Configuration
{
CConfiguration* CConfiguration::m_pConfiguration;

CConfiguration::CConfiguration( const std::string& configurationFileName )
: m_pConfigNode(0)
{
	LoadFile(configurationFileName);
}

CConfiguration::~CConfiguration()
{
	if ( 0!= m_pConfigNode )
	{	
		delete m_pConfigNode;
	}
}

bool CConfiguration::LoadFile( const std::string& configurationFileName )
{
	bool retVal(false);

	//printf("opening the file: %s\n", configurationFileName.c_str());
	XMLNode xMainNode=XMLNode::openFileHelper(configurationFileName.c_str(),sConst_ConfigurationMainNode);

	m_pConfigNode = ScanNode( xMainNode );
	
	return retVal;
}

CConfigNode* CConfiguration::ScanNode( const XMLNode& node )
{
	
	std::string nodeName = node.isAttributeSet(sConst_ConfigurationTag_KeyName) ? node.getAttribute(sConst_ConfigurationTag_KeyName) : std::string("n/a");
	CConfigNode* pConfigNode = new CConfigNode(nodeName);
	if ( 0 != pConfigNode )
	{
		//scan the nodes first
		UInt32 noOfNodes( node.nChildNode(sConst_ConfigurationNode));
		for(UInt32 nodeIdx = 0 ; nodeIdx < noOfNodes ; ++nodeIdx )
		{
			const XMLNode& subnode = node.getChildNode( sConst_ConfigurationNode , nodeIdx );

			const std::string& subnodeName = subnode.getAttribute(sConst_ConfigurationTag_KeyName);
			if (!subnodeName.empty())
			{
				CConfigNode* targetNodeStructure = ScanNode(subnode);
				if ( 0 != targetNodeStructure )
				{
					pConfigNode->AddConfigNode(subnodeName, targetNodeStructure );
				}
			}
		}
		//scan parameters
		UInt32 noOfParameters( node.nChildNode(sConst_ConfigurationParameter));
		for(UInt32 paramIdx = 0 ; paramIdx < noOfParameters ; ++paramIdx )
		{
			const XMLNode& paramNode = node.getChildNode( sConst_ConfigurationParameter , paramIdx );

			const std::string& parameterName = paramNode.getAttribute(sConst_ConfigurationTag_KeyName);
			const std::string& parameterType = paramNode.getAttribute(sConst_ConfigurationTag_Type);
			const std::string& parameterValue= paramNode.getText();
		
			pConfigNode->AddParameter(parameterName, parameterType, parameterValue);
		}
	}

	return pConfigNode;
}

const CConfigNode* CConfiguration::GetConfiguration(const std::string& configurationFileName)
{
	if ( 0 == m_pConfiguration )
	{
		m_pConfiguration = new CConfiguration( configurationFileName );
	}
	return m_pConfiguration->m_pConfigNode;
}

void CConfiguration::ReleaseConfiguration()
{
	if ( 0 != m_pConfiguration )
	{
		delete m_pConfiguration;
	}
	m_pConfiguration = 0;
}

}
