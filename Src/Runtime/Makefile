OUTPUT= libRuntime
OBJ = CMessenger.o CMessage.o CSharedStorage.o CExecutable.o executableMain.o CStubBase.o CTimerManager.o CRuntimeUnit.o

include ../../DevEnv/staticLibSettings

CMessenger.o:	CMessenger.cpp CMessenger.h
CMessage.o:	CMessage.cpp CMessage.h
CSharedStorage.o:	CSharedStorage.h CSharedStorage.cpp
CExecutable.o:	CExecutable.h CExecutable.cpp
executableMain.o: executableMain.c
CStubBase.o: CStubBase.h CStubBase.cpp
CTimerManager.o: CTimerManager.h CTimerManager.cpp ITimerManager.h ITimerListener.h
CRuntimeUnit.o: CRuntimeUnit.h CRuntimeUnit.cpp
