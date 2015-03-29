#ifndef JOYSTICK_CJOYSTICK_H
#define JOYSTICK_CJOYSTICK_H

#include <Runtime/CRuntimeUnit.h>
#include "CInputHandler.h"

namespace Joystick
{
class CJoystick : public Runtime::CRuntimeUnit
{
 public:
  
  CJoystick();
  virtual ~CJoystick();
  virtual void Initialize();

	virtual void Shutdown();
private:
	CInputHandler m_handler;
};
}

#endif 
