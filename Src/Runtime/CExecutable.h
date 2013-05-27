#ifndef RUNTIME_CEXECUTABLE_H
#define RUNTIME_CEXECUTABLE_H
#include "../Global/GlobalTypes.h"
#include "CMessenger.h"

namespace Runtime
{
class CExecutable;
}

Runtime::CExecutable* __pExecutable;

namespace Runtime
{

class CExecutable
{
public:
	CExecutable()
	{
		__pExecutable = this;
	}
	virtual ~CExecutable() {};

	void InitModule(int argc, char** argv)
	{
		for (UInt8 i = 0 ; i < argc ; ++i )
		{
			std::string argString(argv[i]);
			m_arguments.push_back(argString);
		}
	}

	virtual void Initialize() {} ;
	virtual Int32 Run() = 0 ;
	virtual void Shutdown() {} ;

protected:
	const std::string& GetArgument( const UInt8& argNo )
	{
		if ( argNo < m_arguments.size() )
		{
			return m_arguments[argNo];
		}

		return s_cEmptyString;
	}

	Int32 GetArgumentCount()
	{
		return m_arguments.size();
	}

private:
	tStringVector m_arguments;
};

}

int main(int argc, char** argv )
{
	int retVal = 0;

	if ( 0 != __pExecutable )
	{
		__pExecutable->InitModule(argc,argv);

		retVal = __pExecutable->Run();

		__pExecutable->Shutdown();
	}

	return retVal;
}




#endif

