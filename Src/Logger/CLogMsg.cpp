#include "CLogMsg.h"
#include "ILogAgent.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "LoggerConst.h"
namespace Logger
{
//initialize statics
ILogAgent* CLogMsg::s_logAgent = 0;
UInt8 CLogMsg::s_uintLogSetting = 0;
UInt32 CLogMsg::s_uint32_unitRuntimeId = 0;

CLogMsg::CLogMsg()
: m_debugZone( 0 )
, m_codeFileName( 0 )
, m_codeFileNameSize( 0 )
, m_line(0)
, m_logText(0)
, m_logTextSize(0)
{
}

CLogMsg::CLogMsg( const UInt8 debugZone, const char* srcFileName, const UInt32 srcLineNo)
: m_debugZone( debugZone )
, m_codeFileName( srcFileName )
, m_codeFileNameSize(0)
, m_line(srcLineNo)
, m_logText(0)
{
	m_codeFileNameSize = strlen(m_codeFileName) + 1 ;
}

CLogMsg::~CLogMsg()
{
}

void CLogMsg::LogText( const Int8* logText, ... )
{
	Int8 buffer[MAX_LOG_TEXT_LENGTH];
	
	va_list parameters ;
	va_start( parameters, logText);
	m_logTextSize = vsnprintf(buffer, MAX_LOG_TEXT_LENGTH ,logText, parameters);
	m_logTextSize += 1;//the one for null character
	va_end(parameters);

	m_logText = buffer;

	if ( 0 != s_logAgent )
	{
		s_logAgent->IssueLog(*this);
	}

}

size_t CLogMsg::Serialize(Int8* buffer) const
{
	Int8* bufferPosition(buffer);

	memcpy(bufferPosition, &s_uint32_unitRuntimeId, sizeof(s_uint32_unitRuntimeId));
	bufferPosition += sizeof(s_uint32_unitRuntimeId);
	
	memcpy(bufferPosition, &m_debugZone, sizeof(m_debugZone));
	bufferPosition +=sizeof(m_debugZone);

	memcpy(bufferPosition, &m_line, sizeof(m_line));
	bufferPosition +=sizeof(m_line);

	memcpy(bufferPosition, &m_logTextSize, sizeof(m_logTextSize));
	bufferPosition +=sizeof(m_logTextSize);

	memcpy(bufferPosition, m_logText, m_logTextSize);
	bufferPosition += m_logTextSize;

	memcpy(bufferPosition, &m_codeFileNameSize, sizeof(m_codeFileNameSize) );
	bufferPosition += sizeof(m_codeFileNameSize);

	memcpy(bufferPosition, m_codeFileName ,m_codeFileNameSize);
	bufferPosition += m_codeFileNameSize;

	return ( bufferPosition - buffer );
}

bool CLogMsg::Deserialize(const Int8* buffer, size_t bufferSize)
{
	bool retVal( true );

	memcpy(&s_uint32_unitRuntimeId, buffer, sizeof(s_uint32_unitRuntimeId) );
	buffer += sizeof(s_uint32_unitRuntimeId);

	memcpy(&m_debugZone, buffer, sizeof(m_debugZone) );
	buffer += sizeof(m_debugZone);

	memcpy(&m_line, buffer, sizeof(m_line) );
	buffer += sizeof(m_line);

	memcpy(&m_logTextSize, buffer, sizeof(m_logTextSize));
	buffer += sizeof(m_logTextSize);

	m_logText = buffer;
	buffer += m_logTextSize;

	memcpy(&m_codeFileNameSize, buffer ,sizeof(m_codeFileNameSize));
	buffer += sizeof(m_codeFileNameSize);
	
	m_codeFileName = buffer;

	return retVal;
}

const char* CLogMsg::ToString() const
{
	printf("-->|%03d|%03d|%-60s|%s(%d)\n", 	s_uint32_unitRuntimeId, 
																					m_debugZone,
																					m_logText, 
																					m_codeFileName, 
																					m_line);
	return 0;
}
}
