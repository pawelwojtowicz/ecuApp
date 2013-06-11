#ifndef CONFIGURATION_CONFIGURATION_H
#define CONFIGURATION_CONFIGURATION_H
#include "GlobalTypes.h"
#include "CConfigNode.h"
#include "CParameter.h"


class XMLNode;

namespace Configuration
{
class CConfiguration
{
	CConfiguration( const std::string& configurationFileName );
	virtual ~CConfiguration();

	bool LoadFile( const std::string& configurationFileName );

	CConfigNode* ScanNode( const XMLNode& node );
public:
	static const CConfigNode* GetConfiguration(const std::string& configurationFileName);
	void ReleaseConfiguration();
private:
	static CConfiguration* m_pConfiguration;

	CConfigNode* m_pConfigNode;
};
}
#endif
