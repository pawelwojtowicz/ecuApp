#ifndef TTS_CTTSENGINE_H
#define TTS_CTTSENGINE_H
#include <GlobalTypes.h>
#include <flite/flite.h>

namespace TTS
{

class CTTSEngine
{
public:
	CTTSEngine();
	virtual ~CTTSEngine();
	
	bool Initialize();
	void Shutdown();
	
	bool IsInitialized();
	
	bool Say(const std::string& text );
	
private:
	cst_voice* m_pTTSVoice;
};
}
#endif
