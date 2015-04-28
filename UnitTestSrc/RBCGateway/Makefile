OUTPUT=test_RBCGateway
OBJ=test_CMsgSetCommMode.o CMsgSetCommMode.o CMsgBase.o test_CMsgSetAllMotors.o CMsgSetAllMotors.o
VPATH=$(SUBJ_PATH)/RBCGateway

include ../../DevEnv/unitTestSettings

LFLAGS+= -lUCL -lrt

test_CMsgSetCommMode.o:	test_CMsgSetCommMode.cpp
test_CMsgSetAllMotors.o: test_CMsgSetAllMotors.cpp
CMsgSetCommMode.o: CMsgSetCommMode.cpp CMsgSetCommMode.h
CMsgSetAllMotors.o:	CMsgSetAllMotors.cpp CMsgSetAllMotors.h
CMsgBase.o: CMsgBase.cpp CMsgBase.h
