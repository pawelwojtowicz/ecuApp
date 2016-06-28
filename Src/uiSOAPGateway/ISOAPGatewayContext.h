#ifndef UISOAPGATEWAY_ISOAPGATEWAYCONTEXT_H
#define UISOAPGATEWAY_ISOAPGATEWAYCONTEXT_H

#include <ControllerInterface/IControllerProxy.h>
#include <TTSInterface/ITTSProxy.h>

namespace uiSOAPGateway
{

class ISOAPGatewayContext
{
public:
  ISOAPGatewayContext() {};
  virtual ~ISOAPGatewayContext() {};

  virtual Controller::IControllerProxy& GetControllerProxy() = 0;

  virtual TTS::ITTSProxy& GetText2SpeechProxy() = 0;


private:
  ISOAPGatewayContext(const ISOAPGatewayContext&);
  ISOAPGatewayContext& operator=(const ISOAPGatewayContext&);
};
}
#endif