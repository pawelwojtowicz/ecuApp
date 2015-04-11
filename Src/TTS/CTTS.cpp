#include "CTTS.h"
#include <TTSInterface/TTSInterfaceConst.h>
#include <Logger/Logger.h>

TTS::CTTS gs;

namespace TTS
{

CTTS::CTTS()
: Runtime::CRuntimeUnit("TextToSpeach", s_TTSQueueName)
, m_ttsStub(GetMessenger())
, m_ttsEngine()
{
}

CTTS::~CTTS()
{

}

void CTTS::Initialize()
{
// important - initialize the messenger
  CRuntimeUnit::Initialize();
// important - initialize the timer manager
  InitializeTimerManager();
  
  m_ttsStub.Initialize(this);
  
  bool status = m_ttsEngine.Initialize();
  
	InitDone(status);
}

void CTTS::Say( const std::string& phrase )
{
	RETAILMSG(INFO,("TTS-Saying [%s] - begin ",phrase.c_str()));
  m_ttsEngine.Say(phrase);
	RETAILMSG(INFO,("TTS-Saying - done"));

}

void CTTS::Shutdown()
{
	m_ttsEngine.Shutdown();
}

}
