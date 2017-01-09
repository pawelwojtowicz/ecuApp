#pragma once
#include "IModemListener.h"

namespace GSMDaemon
{
class IGSMDaemonConfiguration;
class IGSMModemService;

class CModemManager : public IModemListener
{
public:
	CModemManager();
	virtual ~CModemManager();

	bool Initialize( const IGSMDaemonConfiguration& configuration, IGSMModemService* pModemService);
	void Shutdown();

private:
	IGSMModemService* m_pModemService;
};
}
