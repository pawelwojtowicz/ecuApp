#ifndef EXAMPLEAPP_CEXAMPLEAPP_H
#define EXAMPLEAPP_CEXAMPLEAPP_H

#include <Runtime/CRuntimeUnit.h>
#include <Runtime/ITimerListener.h>

namespace ExampleApp
{
class CExampleApp : public Runtime::CRuntimeUnit, Runtime::ITimerListener
{
 public:
  
  CExampleApp();
  virtual ~CExampleApp();
  virtual void Initialize();

  virtual void NotifyTimer( const Int32& timerId );

private:
  Int32 m_timer1Id;

  Int32 m_shutdownTimer;

  Int32 m_iddleTimer;

};

}

#endif 
