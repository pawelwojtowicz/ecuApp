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

	std::string path("mainNode2.KolejneZagniezdzenie3");
	
	const Configuration::CConfigNode* pConfig = Configuration::CConfiguration::GetConfiguration(configFileName)->GetConfigNode(path);
	
	if (0 != pConfig )
	{
		printf("jest znaleziony node\n");

		const Configuration::CParameter* pParameter = pConfig->GetParameter("Par2");

		if (pParameter->IsValid() )
		{
			Int8 value(0);
			pParameter->GetInt8(value);

			printf("value = %d\n", value );
		}
		else
		{
			printf("Invalid parameter\n");
		}
	}
}

void CNewProcess::NotifyTimer( const Int32& timerId )
{
}

