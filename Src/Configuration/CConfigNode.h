#ifndef CONFIGURATION_CCONFIGNODE_H
#define CONFIGURATION_CCONFIGNODE_H

#include <GlobalTypes.h>
#include <map>
#include "CParameter.h"

namespace Configuration
{
class CConfigNode
{
typedef std::map<std::string, CConfigNode*> tName2ConfigNodeMap;
typedef tName2ConfigNodeMap::const_iterator tName2ConfigNodeConstIter;

typedef std::map<std::string, CParameter*> tName2ParameterMap;
typedef tName2ParameterMap::const_iterator tName2ParameterConstIter; 
public:
	CConfigNode(const std::string& nodeName);
	virtual ~CConfigNode();
	void AddConfigNode( const std::string& nodeName, CConfigNode* pConfigNode );
	void AddParameter( const std::string& parameterName, const std::string& type, const std::string& value );	

	const std::string& GetConfigNodeName() const {return m_nodeName;};

	const CConfigNode* GetConfigNode(const std::string& configNodeName) const;
	const CParameter* GetParameter( const std::string& parameterName ) const;

	const CConfigNode* GetFirstSubnode() const;
	const CConfigNode* GetNextSubnode() const;
private:
	tName2ConfigNodeMap m_configNodesMap;

	tName2ParameterMap m_parametersMap;

	mutable tName2ConfigNodeConstIter m_currentSubnode;

	std::string m_nodeName;
};
}

#endif
