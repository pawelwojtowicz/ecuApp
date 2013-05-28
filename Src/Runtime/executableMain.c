#include "CExecutable.h"
#include <stdio.h>

Runtime::CExecutable* __pExecutable;

int main(int argc, char** argv )
{
	int retVal = 0;
	printf("wszedl\n");

	if ( 0 != __pExecutable )
	{
		printf("wszedl1\n");

		__pExecutable->InitModule(argc,argv);

		retVal = __pExecutable->Run();

		__pExecutable->Shutdown();
	}

	return retVal;
}

