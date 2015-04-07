#ifndef TTS_CTTS_H
#define TTS_CTTS_H
#include <Runtime/CRuntimeUnit.h>
#include <TTSInterface/ITTSServices.h>
#include <TTSInterface/CTTSStub.h>
#include "CTTSEngine.h"

namespace TTS
{
class CTTS : public Runtime::CRuntimeUnit, public ITTSServices
{
public:
	CTTS();
	virtual ~CTTS();
	virtual void Initialize();
	virtual void Shutdown();
private:
	virtual void Say( const std::string& phrase );

private:
	CTTSStub m_ttsStub;

	CTTSEngine m_ttsEngine;
};
}
#endif
