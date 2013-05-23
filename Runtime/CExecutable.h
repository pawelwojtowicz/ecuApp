#ifndef UCL_CEXECUTABLE_H
#define UCL_CEXECITABLE_H
#include "UCLTypes.h"

namespace UCL
{

class CExecutable
{
public:
	CExecutable(int argc, char** argv);
	virtual ~CExecutable();

	virtual void Initialize();
	virtual void Run();
	virtual void Shutdown();

public:


private:
	tStringVector m_arguments;
};


}


#endif

