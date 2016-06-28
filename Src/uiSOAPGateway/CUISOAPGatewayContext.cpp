#include "CUISOAPGatewayContext.h"

namespace uiSOAPGateway
{

CUISOAPGatewayContext::CUISOAPGatewayContext(Runtime::IMessenger& rMessenger)
: m_controllerProxy(rMessenger)
, m_ttsProxy(rMessenger)
{

}

CUISOAPGatewayContext::~CUISOAPGatewayContext()
{

}

bool CUISOAPGatewayContext::Initialize()
{
  return true;
}
bool CUISOAPGatewayContext::Shutdown()
{
  return true;
}

Controller::IControllerProxy& CUISOAPGatewayContext::GetControllerProxy()
{
  return m_controllerProxy;
}

TTS::ITTSProxy& CUISOAPGatewayContext::GetText2SpeechProxy()
{
  return m_ttsProxy;
}

}
