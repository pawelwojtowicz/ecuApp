#include "CNewProcess.h"
#include "Runtime/CMessenger.h"
#include "Runtime/CMessage.h"
#include <unistd.h>
#include <Configuration/CConfiguration.h>

CNewProcess gInstance;

CNewProcess::CNewProcess()
: CRuntimeUnit("TestProcess", "/TestowaQueue")
, m_timer1Id(0)
, m_timer2Id(0)
{
	printf("Konstruktor\n");
}

CNewProcess::~CNewProcess()
{
}

void CNewProcess::Initialize()
{
	printf("Initialize\n");
	const char configFileName[] = {"/home/tpdev/Programowanie/lnxEmbdDevice/Configuration/Configuration.xml"};
	
	Configuration::CConfiguration::GetConfiguration(configFileName);
}

void CNewProcess::NotifyTimer( const Int32& timerId )
{
}

