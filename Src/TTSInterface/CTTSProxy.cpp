#include "CTTSProxy.h"
#include "TTSInterfaceConst.h"
#include <Runtime/IMessenger.h>
#include <Runtime/CMessage.h>


namespace TTS
{
CTTSProxy::CTTSProxy(Runtime::IMessenger& rMessenger)
: Runtime::CProxyBase(rMessenger, s_TTSQueueName)

{
}

CTTSProxy::~CTTSProxy()
{
}

bool CTTSProxy::Say(const std::string& phrase)
{
	Runtime::CMessage initDoneMsg(256);
	initDoneMsg.SetMessageId(msgId_TTS_SayPhrase);
	initDoneMsg.SetMsgPrio(255);
	initDoneMsg.SetTargetId(GetTargetQueueId());
	initDoneMsg.SetValue(phrase);

	return GetMessenger().PostMessage(initDoneMsg);
}

}
