#include "CTTSEngine.h"


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
	
	m_pTTSVoice = flite_voice_select("kal");
	
	
	return true;
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
