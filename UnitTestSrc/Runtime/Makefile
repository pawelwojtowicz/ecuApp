OUTPUT=test_Messenger
OBJ=CTest_Messenger.o CMessenger.o CMessage.o CUDSMockHelper.o CSubscriberMock.o CTest_CSharedStorage.o CSharedStorage.o
VPATH=$(SUBJ_PATH)/Runtime

include ../../DevEnv/unitTestSettings
LFLAGS+= -lUCL -lrt

CMessage.o:	CMessage.cpp CMessage.h
CMessenger.o:	CMessenger.cpp CMessenger.h
CTest_Messenger.o:	CTest_Messenger.cpp
CUDSMockHelper.o: CUDSMockHelper.cpp CUDSMockHelper.h
CSubscriberMock.o: CSubscriberMock.cpp CSubscriberMock.h
CTest_CSharedStorage.o: CTest_CSharedStorage.cpp
CSharedStorage.o: CSharedStorage.cpp CSharedStorage.h
