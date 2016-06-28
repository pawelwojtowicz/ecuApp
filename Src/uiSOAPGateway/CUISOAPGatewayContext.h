#ifndef UISOAPGATEWAY_CUIGATEWAYCONTEXT_H
#define UISOAPGATEWAY_CUIGATEWAYCONTEXT_H
#include "ISOAPGatewayContext.h"
#include <ControllerInterface/CControllerProxy.h>
#include <TTSInterface/CTTSProxy.h>

namespace uiSOAPGateway
{

class CUISOAPGatewayContext: public ISOAPGatewayContext
{
public:
  CUISOAPGatewayContext(Runtime::IMessenger& rMessenger);
  virtual ~CUISOAPGatewayContext();

  bool Initialize();
  bool Shutdown();

private:

  virtual Controller::IControllerProxy& GetControllerProxy();

  virtual TTS::ITTSProxy& GetText2SpeechProxy();


private:
  CUISOAPGatewayContext(const CUISOAPGatewayContext&);
  CUISOAPGatewayContext& operator=(const CUISOAPGatewayContext&);

  Controller::CControllerProxy m_controllerProxy;

  TTS::CTTSProxy m_ttsProxy;
};
}
#endif