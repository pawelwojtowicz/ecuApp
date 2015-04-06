#include "CTTSEngine.h"

extern "C" 
{
cst_voice *register_cmu_us_kal(const char*);				// mans voice
cst_voice *register_cmu_us_awb(const char *voxdir); // mans voice
cst_voice *register_cmu_us_rms(const char *voxdir);	// slappy mans voice
cst_voice *register_cmu_us_slt(const char *voxdir); // womans voice
}


namespace TTS
{
CTTSEngine::CTTSEngine()
: m_pTTSVoice(0)
{
}

CTTSEngine::~CTTSEngine()
{
}

bool CTTSEngine::Initialize()
{
	flite_init();
	
	m_pTTSVoice = register_cmu_us_slt(NULL);
	
	
	
	return ( 0 != m_pTTSVoice );
}

void CTTSEngine::Shutdown()
{

}

bool CTTSEngine::IsInitialized()
{
	return ( 0 != m_pTTSVoice );
}

bool CTTSEngine::Say(const std::string& text )
{
	float phraseLength(0);
	
	if ( 0 != m_pTTSVoice )
	{
		phraseLength = flite_text_to_speech( text.c_str() , m_pTTSVoice , "play" );
	}

	return ( 0 != phraseLength );
}

}
