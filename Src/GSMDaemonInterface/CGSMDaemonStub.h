#pragma once

#include <Runtime/CStubBase.h>
#include <ATProtocolEngine/IATLineConsumer.h> 

namespace Runtime
{
class CMessenger;
class CMessage;
}

namespace GSMDaemon
{
class IGSMDaemonService;

class CGSMDaemonStub: public Runtime::CStubBase, public ATProtocolEngine::IATLineConsumer
{
public:
	CGSMDaemonStub( Runtime::IMessenger& rMessenger );
	virtual ~CGSMDaemonStub();

	virtual bool Initialize(IGSMDaemonService* pService);
	virtual bool Shutdown();
	
private:
	// ATProtocolEngine::IATLineConsumer
	void NotifyATResponseExtracted( const std::string line );
	void NotifyATPromptExtracted( const std::string line );

private:
	virtual void HandleMessage(Runtime::CMessage& rMessage);

private:
	IGSMDaemonService* m_pGSMDaemonService;


};

}

