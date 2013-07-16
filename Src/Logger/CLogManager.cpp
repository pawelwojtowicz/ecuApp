#include "CLogManager.h"
#include "LoggerConst.h"
#include "Logger.h"
#include "Configuration/CConfiguration.h"
#include "ILogTarget.h"
#include <stdio.h>

static const char sConstCfg_DefaultLogLevelNodeName[] = {"DefaultDebugLevel"};
static const char sConstCfg_InfoZoneName[]						=	{"Info"};
static const char sConstCfg_ErrorZoneName[]						= {"Error"};
static const char sConstCfg_WarningZoneName[]					= {"Warning"};
static const char sConstCfg_DataZoneName[]						= {"Data"};
static const char sConstCfg_Detail1ZoneName[]					= {"Detail1"};
static const char sConstCfg_Detail2ZoneName[]					= {"Detail2"};

namespace Logger
{
CLogManager::CLogManager()
: m_running(true)
, m_loggerQueueDescriptor(-1)
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

	}
	else
	{
		printf("No Logger configuration available - using very basic defaults\n");
	}

	mq_attr queueAttributes;
	queueAttributes.mq_flags = 0;
	queueAttributes.mq_maxmsg = MAX_LOGGER_QUEUE_SIZE;
	queueAttributes.mq_msgsize = MAX_LOGGER_MSG_SIZE;

	m_loggerQueueDescriptor = mq_open( s_LoggerQueue , O_RDWR|O_CREAT, S_IRWXU, &queueAttributes);

	if ( -1 != m_loggerQueueDescriptor )
	{
		Start();
	}
	else
	{
		printf("Failed to initialize Logger Queue - no logging dude");
	}

	return ( -1 != m_loggerQueueDescriptor );
}

void CLogManager::Shutdown()
{
	m_running = false;

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

	while ( m_running )
	{
		logMsgSize = mq_receive( m_loggerQueueDescriptor, (char*)logMsgBuffer, MAX_LOGGER_MSG_SIZE, &priority );
		if (logMessage.Deserialize(logMsgBuffer, logMsgSize ) )
		{
			logMessage.SetSourceShortName(m_runtimeDictionary[ logMessage.GetLogSrcRuntimeId()].c_str());
			for(logTargetIter = m_targetList.begin() ; m_targetList.end() != logTargetIter ; ++logTargetIter)
			{
				(*logTargetIter)->LogToTarget( logMessage );
			}
			logMessage.ToString();
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
}
