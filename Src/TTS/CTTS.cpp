#include "CTTS.h"
#include <Logger/Logger.h>

TTS::CTTS gs;

namespace TTS
{

CTTS::CTTS()
: Runtime::CRuntimeUnit("TextToSpeach", "TTS_Q")
{
}

CTTS::~CTTS()
{

}

void CTTS::Initialize()
{
	// important - initialize the messenger
  CRuntimeUnit::Initialize();
  
  m_ttsEngine.Initialize();
  
  m_ttsEngine.Say("TTS works fine - let's proceed with the further steps");

	InitDone(true);
}

void CTTS::Shutdown()
{
	m_ttsEngine.Shutdown();
}

}
