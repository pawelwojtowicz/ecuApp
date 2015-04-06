#include "CTTS.h"
#include <Logger/Logger.h>
#include <stdio.h>

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

	bool returnValue = m_ttsEngine.Say("This is a test , please - let us know, if everything is fine");
	
	printf("\nDupa dupa %d",returnValue);
	
	InitDone(true);
}

void CTTS::Shutdown()
{
	m_ttsEngine.Shutdown();
}

}
