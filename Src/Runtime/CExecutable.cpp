#include "CExecutable.h"

namespace Runtime
{

CExecutable::CExecutable()
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

}

