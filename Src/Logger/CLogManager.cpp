#include "CLogManager.h"
#include "LoggerConst.h"
#include "Logger.h"
#include <Configuration/CConfiguration.h>
#include <UCL/CUnixDomainSocket.h>
#include <UCL/SystemEnvironment.h>
#include "CConsoleTarget.h"
#include "CSyslogTarget.h"
#include <stdio.h>
#include <errno.h>

static const char sConstCfg_DefaultLogLevelNodeName[] = {"DefaultDebugLevel"};
static const char sConstCfg_InfoZoneName[]						=	{"Info"};
static const char sConstCfg_ErrorZoneName[]						= {"Error"};
static const char sConstCfg_WarningZoneName[]					= {"Warning"};
static const char sConstCfg_DataZoneName[]						= {"Data"};
static const char sConstCfg_Detail1ZoneName[]					= {"Detail1"};
static const char sConstCfg_Detail2ZoneName[]					= {"Detail2"};

static const char sConstCfg_LoggerTargetsNodeName[]		= {"LogTargets"};
static const char sConstCfg_LoggerTargetType[]				= {"Type"};
static const char sConstCfg_LoggerTargetActive[]			= {"Active"};
static const char sConstCfg_LoggerTypeName_Console[]	= {"CONSOLE"};
static const char sConstCfg_LoggerTypeName_Syslog[]		= {"SYSLOG"};

namespace Logger
{
CLogManager::CLogManager()
: m_running(true)
, m_pSocket(new UCL::CUnixDomainSocket)
, m_defaultLogLevel(0)
{
	m_runtimeDictionary.resize(1);
	m_runtimeDictionary[0] = std::string("CTR");
}

CLogManager::~CLogManager()
{
}

bool CLogManager::Initialize(const Configuration::CConfigNode* configNode)
{
	if ( 0 != configNode )
	{
		const Configuration::CConfigNode* pDefaultLogLevelConfig = configNode->GetConfigNode(sConstCfg_DefaultLogLevelNodeName);
		
		m_defaultLogLevel = ReadDebugLevelConfig(pDefaultLogLevelConfig);

		ConfigureLogTargets(configNode->GetConfigNode(sConstCfg_LoggerTargetsNodeName));
	}
	else
	{
		printf("No Logger configuration available - using very basic defaults\n");
	}

	m_pSocket->Bind(UCL::SystemEnvironment::ResolvePath(UCL::SystemEnvironment::Dir_Runtime,s_LoggerQueue));
	
	if ( m_pSocket->IsValid() )
	{
		Start();
	}
	else
	{
		printf("Failed to initialize Logger Queue - no logging dude\n");
	}

	return ( m_pSocket->IsValid() );
}

void CLogManager::Shutdown()
{
	m_running = false;
	WaitFor();
	
	CLogMsg logMessage;
	Int8 logMsgBuffer[MAX_LOGGER_MSG_SIZE];
	Int32 logMsgSize(0);
	tTargetIterator logTargetIter;
  UCL::CSocketAddress address;
	
	while (	!m_pSocket->IsEmpty() )
	{
		logMsgSize = m_pSocket->Receive(address, logMsgBuffer, MAX_LOGGER_MSG_SIZE );
		if (logMessage.Deserialize(logMsgBuffer, logMsgSize ) )
		{
			logMessage.SetSourceShortName(m_runtimeDictionary[ logMessage.GetLogSrcRuntimeId()].c_str());
			for(logTargetIter = m_targetList.begin() ; m_targetList.end() != logTargetIter ; ++logTargetIter)
			{
				(*logTargetIter)->LogToTarget( logMessage );
			}
		}	
	}

	m_pSocket->Close();

//stop the threads
	for(tTargetIterator logTargetIter = m_targetList.begin() ; m_targetList.end() != logTargetIter ; ++logTargetIter)
	{
		(*logTargetIter)->Shutdown();
	}
}

void CLogManager::Run()
{
	CLogMsg logMessage;
	Int8 logMsgBuffer[MAX_LOGGER_MSG_SIZE];
	Int32 logMsgSize(0);
	UInt32 priority(0);
	tTargetIterator logTargetIter;
	UCL::CSocketAddress address;
	
	if ( !m_pSocket->IsValid() )
	{
		return;
	}

	while ( m_running )
	{
		m_pSocket->Receive(address, (char*)logMsgBuffer, MAX_LOGGER_MSG_SIZE );
		if (logMessage.Deserialize(logMsgBuffer, logMsgSize ) )
		{
			logMessage.SetSourceShortName(m_runtimeDictionary[ logMessage.GetLogSrcRuntimeId()].c_str());
			for(logTargetIter = m_targetList.begin() ; m_targetList.end() != logTargetIter ; ++logTargetIter)
			{
				(*logTargetIter)->LogToTarget( logMessage );
			}
		}	
	}
}

UInt32 CLogManager::ReadDebugLevelConfig(const Configuration::CConfigNode* pConfigNode)
{
	UInt32 debugLevel(0);

	if ( 0 != pConfigNode )
	{
		if ( pConfigNode->GetParameter(sConstCfg_InfoZoneName)->GetBool(true) )
		{
			debugLevel |= INFO;
		}
		if ( pConfigNode->GetParameter(sConstCfg_ErrorZoneName)->GetBool(true) )
		{
			debugLevel |= ERROR;
		}
		if ( pConfigNode->GetParameter(sConstCfg_WarningZoneName)->GetBool(true) )
		{
			debugLevel |= WARNING;
		}
		if ( pConfigNode->GetParameter(sConstCfg_DataZoneName)->GetBool(true) )
		{
			debugLevel |= DATA;
		}
		if ( pConfigNode->GetParameter(sConstCfg_Detail1ZoneName)->GetBool(true) )
		{
			debugLevel |= DET1;
		}
		if ( pConfigNode->GetParameter(sConstCfg_Detail2ZoneName)->GetBool(true) )
		{
			debugLevel |= DET2;
		}
	}
	return debugLevel;
}

void CLogManager::UpdateSourceDictionary( const tStringVector& dictionary )
{
	UInt32 processCount = dictionary.size();

	m_runtimeDictionary.resize(processCount);

	for ( UInt32 i = 1 ; i < processCount ; ++i )
	{
		m_runtimeDictionary[i] = dictionary[i];
	}
}

void CLogManager::ConfigureLogTargets(const Configuration::CConfigNode* configNode)
{
	if ( 0 != configNode )
	{
		const Configuration::CConfigNode* pTargetConfigNode = configNode->GetFirstSubnode();

		while( 0 != pTargetConfigNode )
		{
			bool targetActive = pTargetConfigNode->GetParameter(sConstCfg_LoggerTargetActive)->GetBool(false);
			
			if (targetActive)
			{
				std::string targetType = pTargetConfigNode->GetParameter(sConstCfg_LoggerTargetType)->GetString("");

				ILogTarget* pLogTarget = CreateLogTarget(targetType);
				if ( 0 != pLogTarget )
				{
					if ( pLogTarget->Initialize(pTargetConfigNode) )
					{
						m_targetList.push_back(pLogTarget);
					}
				}
			}
			else
			{
				printf("Target [%s] inactive\n", pTargetConfigNode->GetConfigNodeName().c_str() );
			}
			pTargetConfigNode = configNode->GetNextSubnode();
		}
	}
}

ILogTarget* CLogManager::CreateLogTarget(const std::string& targetTypeName)
{
	ILogTarget* pLogTarget = 0;

	if (0 == targetTypeName.compare(sConstCfg_LoggerTypeName_Console) )
	{
		pLogTarget = new CConsoleTarget();
	} 
	else if (0 == targetTypeName.compare(sConstCfg_LoggerTypeName_Syslog ) )
	{
		pLogTarget = new CSyslogTarget();
	}
	

	return pLogTarget;
}

}
