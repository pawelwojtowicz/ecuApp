OUTPUT=test_Controller
OBJ=CTest_Controller.o CProcessInfo.o CProcessHandler.o CTest_CSessionManager.o CSessionManager.o
VPATH=$(SUBJ_PATH)/Controller

include ../../DevEnv/unitTestSettings
LFLAGS+= -lUCL -lConfiguration -lLogger

CTest_Controller.o:	CTest_Controller.cpp
CProcessInfo.o:	CProcessInfo.cpp CProcessInfo.h
CProcessHandler.o: CProcessHandler.cpp CProcessHandler.h
CTest_CSessionManager.o: CTest_CSessionManager.cpp
CSessionManager.o: CSessionManager.cpp CSessionManager.h
