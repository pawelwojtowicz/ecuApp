OUTPUT=test_RBCGateway
OBJ=test_CMsgSetCommMode.o CMsgSetCommMode.o CMsgBase.o
VPATH=$(SUBJ_PATH)/RBCGateway

include ../../DevEnv/unitTestSettings

LFLAGS+= -lUCL -lrt

test_CMsgSetCommMode.o:	test_CMsgSetCommMode.cpp
CMsgSetCommMode.o: CMsgSetCommMode.cpp CMsgSetCommMode.h
CMsgBase.o: CMsgBase.cpp CMsgBase.h
