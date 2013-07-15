#ifndef LOGGER_CLOGMSG_H
#define LOGGER_CLOGMSG_H
#include <GlobalTypes.h>
namespace Logger
{
class ILogAgent;

class CLogMsg
{
public:
	CLogMsg();
	CLogMsg( const UInt8 debugZone, const char* srcFileName, const UInt32 srcLineNo);
	virtual ~CLogMsg();
	static inline bool ZoneEnabled(UInt8 queryZone) { return 0!= (	s_uintLogSetting & queryZone );};

	void LogText( const Int8* logText, ... );

	size_t Serialize(Int8* buffer) const ;
	bool Deserialize(const Int8* buffer, size_t bufferSize);

	const char* ToString() const;

	static void SetLogAgent( ILogAgent* pLogAgent ) { s_logAgent = pLogAgent;} ;

	static void SetDebugLevel( const UInt8 debugLevel ) { s_uintLogSetting = debugLevel ; };

	static void SetUnitId( const UInt32 unitId ) { s_uint32_unitRuntimeId = unitId; };
private:
	// loging agent - puts the logs into the master log queue.
	static ILogAgent* s_logAgent;

	// logging level setting
	static UInt8 s_uintLogSetting;

	// runtime id of the process - will be used in log manager to name the source.
	static UInt32 s_uint32_unitRuntimeId;

	// specifies the debug level on the log entry
	UInt8 m_debugZone;

	// indicates the name of the file, where the log was issued
	const char* m_codeFileName;
	size_t m_codeFileNameSize;
	// indicates the line, where the log was issued
	UInt32 m_line;

	// the text of the log indeed.
	const char* m_logText;
	size_t m_logTextSize;
};
}
#endif
