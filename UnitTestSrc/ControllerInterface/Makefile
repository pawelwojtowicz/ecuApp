OUTPUT=test_ControllerInterface
OBJ=CTest_CPublicProcessInfo.o CPublicProcessInfo.o

VPATH=$(SUBJ_PATH)/ControllerInterface

include ../../DevEnv/unitTestSettings
LFLAGS+= -lrt -lConfiguration -lLogger -lUCL

CTest_CPublicProcessInfo.o: CTest_CPublicProcessInfo.cpp
CPublicProcessInfo.o: CPublicProcessInfo.cpp CPublicProcessInfo.h
