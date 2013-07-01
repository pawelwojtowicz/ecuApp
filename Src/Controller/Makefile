OUTPUT= controller
OBJ= CController.o CWatchdogManager.o CProcessManager.o

include ../../DevEnv/executableSettings

LFLAGS+= -lControllerInterface -lRuntime

CController.o:	CController.cpp CController.h
CWatchdogManager.o: CWatchdogManager.cpp CWatchdogManager.h
CProcessManager.o: CProcessManager.cpp CProcessManager.h

