#ifndef LOGGER_CLOGMANAGER_H
#define LOGGER_CLOGMANAGER_H

#include <GlobalTypes.h>
#include <UCL/CThread.h>
#include <list>
#include <vector>
namespace Configuration
{
class CConfigNode;
}

namespace UCL
{
class IUnixDomainSocket;
}

namespace Logger
{
class ILogTarget;

class CLogManager : public UCL::CThread
{
	typedef std::list<ILogTarget*> tTargetList;
	typedef tTargetList::iterator tTargetIterator;

public:
	CLogManager();
	virtual ~CLogManager();
	
	void UpdateLoggerPrefixTable();

	bool Initialize(const Configuration::CConfigNode* configNode);

	void Shutdown();

	virtual void Run();

	inline const UInt32 GetDefaultDebugZones() const { return m_defaultLogLevel; };

	void UpdateSourceDictionary( const tStringVector& dictionary );

public:
	static UInt32 ReadDebugLevelConfig(const Configuration::CConfigNode* configNode);
private:
	void ConfigureLogTargets(const Configuration::CConfigNode* configNode);

	ILogTarget* CreateLogTarget(const std::string& targetTypeName);
private:
	//running flag - clear during shutdown
	bool m_running;

	//logger queue descriptor
	UCL::IUnixDomainSocket* m_pSocket;

	//the list of configured/active log targets targets
	tTargetList m_targetList;

	// stores the mapping from the runtime Id to Logger short names
	tStringVector m_runtimeDictionary;

	UInt32 m_defaultLogLevel;
};
}
#endif
