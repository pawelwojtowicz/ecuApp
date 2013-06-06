#ifndef CNEWPROCESS_H
#define CNEWPROCESS_H

#include <stdio.h>
#include "Runtime/CRuntimeUnit.h"
#include "Runtime/ITimerListener.h"

class CNewProcess : public Runtime::CRuntimeUnit
									, public Runtime::ITimerListener
{
public:
	CNewProcess();
	virtual ~CNewProcess();

	virtual void Initialize();

	virtual void NotifyTimer( const Int32& timerId );

private:

	Int32 m_timer1Id;
	Int32 m_timer2Id;
};
#endif
