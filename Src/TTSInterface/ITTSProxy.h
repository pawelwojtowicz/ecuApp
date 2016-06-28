#ifndef TTS_ITTSProxy_H
#define TTS_ITTSProxy_H
#include <Global/GlobalTypes.h>

namespace TTS
{

class ITTSProxy
{
public:
	ITTSProxy() {};
	virtual ~ITTSProxy() {};

	virtual bool Say(const std::string& phrase) = 0;

private:
	ITTSProxy(const ITTSProxy&);
	ITTSProxy& operator=(const ITTSProxy&);
};

}

#endif
