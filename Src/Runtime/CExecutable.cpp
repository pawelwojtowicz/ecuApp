#include "CExecutable.h"
#include <signal.h>
#include <sys/time.h>

void timerHandler( int signalNo )
{
	if (SIGALRM == signalNo )
	{
		__pExecutable->NotifyTimer();
	}
}

namespace Runtime
{

CExecutable::CExecutable(const std::string& unitName)
: m_processName(unitName)
{
	__pExecutable = this;
}

void CExecutable::InitModule(int argc, char** argv)
{
	for (UInt8 i = 0 ; i < argc ; ++i )
	{
		std::string argString(argv[i]);
		m_arguments.push_back(argString);
	}
	Initialize();
}

const std::string& CExecutable::GetArgument( const UInt8& argNo )
{
	if ( argNo < m_arguments.size() )
	{
		return m_arguments[argNo];
	}

	return s_cEmptyString;
}

Int32 CExecutable::GetArgumentCount()
{
	return m_arguments.size();
}

bool CExecutable::InitializeTimer( const UInt32& startAfter )
{
	signal( SIGALRM, timerHandler );

	itimerval delay;
	delay.it_value.tv_sec = startAfter;
	delay.it_value.tv_usec = 0;
	delay.it_interval.tv_sec = 1;
	delay.it_interval.tv_usec = 0;

	return ( 0 != setitimer(ITIMER_REAL, &delay, NULL) );	
}

const std::string& CExecutable::GetUnitName()
{
	return m_processName;
}

}

