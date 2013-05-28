#ifndef RUNTIME_CEXECUTABLE_H
#define RUNTIME_CEXECUTABLE_H
#include "GlobalTypes.h"
#include "CMessenger.h"

namespace Runtime
{

class CExecutable
{
public:
	CExecutable();
	virtual ~CExecutable() {};

	void InitModule(int argc, char** argv);

	virtual void Initialize() {} ;
	virtual Int32 Run() = 0 ;
	virtual void Shutdown() {} ;

protected:
	const std::string& GetArgument( const UInt8& argNo );
	Int32 GetArgumentCount();

private:
	tStringVector m_arguments;
};

}

extern Runtime::CExecutable* __pExecutable;
#endif

