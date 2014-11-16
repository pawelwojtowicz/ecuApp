OUTPUT=test_Controller
OBJ=CTest_Controller.o CProcessInfo.o CProcessHandler.o CTest_CSessionManager_Logic.o CSessionManager.o CTest_CSessionManager_Helpers.o CTest_CProcessManager.o CProcessManager.o CProcessControl.o

#OBJ= CTest_CProcessManager.o CProcessManager.o CProcessInfo.o
VPATH=$(SUBJ_PATH)/Controller

include ../../DevEnv/unitTestSettings
LFLAGS+= -lUCL -lConfiguration -lLogger

CTest_Controller.o:	CTest_Controller.cpp
CProcessInfo.o:	CProcessInfo.cpp CProcessInfo.h
CProcessHandler.o: CProcessHandler.cpp CProcessHandler.h
CTest_CSessionManager_Logic.o: CTest_CSessionManager_Logic.cpp
CTest_CSessionManager_Helpers.o: CTest_CSessionManager_Helpers.cpp
CSessionManager.o: CSessionManager.cpp CSessionManager.h
CTest_CProcessManager.o: CTest_CProcessManager.cpp
CProcessManager.o: CProcessManager.h CProcessManager.cpp
CProcessControl.o: CProcessControl.h CProcessControl.cpp
