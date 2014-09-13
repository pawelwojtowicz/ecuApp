OUTPUT=test_Messenger
OBJ=CTest_Messenger.o CMessenger.o CMessage.o CUDSMockHelper.o
VPATH=$(SUBJ_PATH)/Runtime

include ../../DevEnv/unitTestSettings
LFLAGS+= -lUCL

CMessage.o:	CMessage.cpp CMessage.h
CMessenger.o:	CMessenger.cpp CMessenger.h
CTest_Messenger.o:	CTest_Messenger.cpp
CUDSMockHelper.o: CUDSMockHelper.cpp CUDSMockHelper.h

