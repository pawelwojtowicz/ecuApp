#ifndef TTS_CTTS_H
#define TTS_CTTS_H
#include <Runtime/CRuntimeUnit.h>
#include "CTTSEngine.h"
namespace TTS
{
class CTTS : public Runtime::CRuntimeUnit
{
public:
	CTTS();
	virtual ~CTTS();
	virtual void Initialize();
	virtual void Shutdown();

private:

	CTTSEngine m_ttsEngine;
};
}
#endif
