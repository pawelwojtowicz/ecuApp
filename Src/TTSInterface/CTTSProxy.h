#ifndef TTS_CTTSProxy_H
#define TTS_CTTSProxy_H
#include "ITTSProxy.h"
#include <Runtime/CProxyBase.h>

namespace TTS
{

class CTTSProxy : public ITTSProxy, public Runtime::CProxyBase
{
public:
	CTTSProxy(Runtime::IMessenger& rMessenger);
	virtual ~CTTSProxy();

	virtual bool Say(const std::string& phrase);

private:
	CTTSProxy(const CTTSProxy&);
	CTTSProxy& operator=(const CTTSProxy&);
};

}

#endif
