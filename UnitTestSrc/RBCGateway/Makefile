OUTPUT=test_RBCGateway
OBJ=test_CMsgSetCommMode.o CMsgSetCommMode.o CMsgBase.o test_CMsgSetAllMotors.o CMsgSetAllMotors.o CMsgSetControlMode.o test_CMsgSetControlMode.o CMsgConfigurePID.o test_CMsgConfigurePID.o test_CInitSequenceFileParser.o CInitSequenceFileParser.o test_CMsgResetEncoders.o CMsgResetEncoders.o
VPATH=$(SUBJ_PATH)/RBCGateway

include ../../DevEnv/unitTestSettings

LFLAGS+= -lUCL -lrt

test_CMsgSetControlMode.o:	test_CMsgSetControlMode.cpp
test_CMsgSetCommMode.o:	test_CMsgSetCommMode.cpp
test_CMsgSetAllMotors.o: test_CMsgSetAllMotors.cpp
test_CMsgConfigurePID.o: test_CMsgConfigurePID.cpp
test_CMsgResetEncoders.o: test_CMsgResetEncoders.cpp
CMsgSetCommMode.o: CMsgSetCommMode.cpp CMsgSetCommMode.h
CMsgSetAllMotors.o:	CMsgSetAllMotors.cpp CMsgSetAllMotors.h
CMsgSetControlMode.o:	CMsgSetControlMode.cpp CMsgSetControlMode.h
CMsgConfigurePID.o: CMsgConfigurePID.cpp CMsgConfigurePID.h
CMsgResetEncoders.o: CMsgResetEncoders.cpp CMsgResetEncoders.h
CMsgBase.o: CMsgBase.cpp CMsgBase.h
test_CInitSequenceFileParser.o: test_CInitSequenceFileParser.cpp
CInitSequenceFileParser.o: CInitSequenceFileParser.cpp CInitSequenceFileParser.h

