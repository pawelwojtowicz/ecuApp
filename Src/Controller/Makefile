OUTPUT= controller
OBJ= CController.o CWatchdogManager.o CProcessManager.o CProcessHandler.o

include ../../DevEnv/executableSettings

LFLAGS+= -lControllerInterface -lRuntime -lUCL -lLogger

CController.o:	CController.cpp CController.h
CWatchdogManager.o: CWatchdogManager.cpp CWatchdogManager.h
CProcessManager.o: CProcessManager.cpp CProcessManager.h
CProcessHandler.o: CProcessHandler.cpp CProcessHandler.h

