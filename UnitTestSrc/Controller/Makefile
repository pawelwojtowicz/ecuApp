OUTPUT=test_Controller
OBJ=CTest_Controller.o CProcessInfo.o
VPATH=$(SUBJ_PATH)/Controller

include ../../DevEnv/unitTestSettings
LFLAGS+= -lUCL -lConfiguration -lLogger

CTest_Controller.o:	CTest_Controller.cpp
CProcessInfo.o:	CProcessInfo.cpp CProcessInfo.h
