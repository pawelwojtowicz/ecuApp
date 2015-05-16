OUTPUT=test_RBCGateway
OBJ=test_CMsgSetCommMode.o CMsgSetCommMode.o CMsgBase.o test_CMsgSetAllMotors.o CMsgSetAllMotors.o CMsgSetControlMode.o test_CMsgSetControlMode.o CMsgConfigurePID.o test_CMsgConfigurePID.o test_CInitSequenceFileParser.o CInitSequenceFileParser.o test_CMsgResetEncoders.o CMsgResetEncoders.o test_CMsgSetSpeed.o CMsgSetSpeed.o CMsgSetPosition.o test_CMsgSetPosition.o CMsgSetMotorSpeed.o CMsgSetMotorPosition.o test_CMsgSetMotorSpeed.o test_CMsgSetMotorPosition.o test_CMsgSetIO.o CMsgSetIO.o
VPATH=$(SUBJ_PATH)/RBCGateway

include ../../DevEnv/unitTestSettings

LFLAGS+= -lUCL -lrt

test_CMsgSetControlMode.o:	test_CMsgSetControlMode.cpp
test_CMsgSetCommMode.o:	test_CMsgSetCommMode.cpp
test_CMsgSetAllMotors.o: test_CMsgSetAllMotors.cpp
test_CMsgConfigurePID.o: test_CMsgConfigurePID.cpp
test_CMsgResetEncoders.o: test_CMsgResetEncoders.cpp
test_CMsgSetSpeed.o: test_CMsgSetSpeed.cpp
test_CMsgSetMotorSpeed.o: test_CMsgSetMotorSpeed.cpp
test_CMsgSetMotorPosition.o: test_CMsgSetMotorPosition.cpp
test_CMsgSetPosition.o: test_CMsgSetPosition.cpp
test_CMsgSetIO.o: test_CMsgSetIO.cpp
CMsgSetCommMode.o: CMsgSetCommMode.cpp CMsgSetCommMode.h
CMsgSetAllMotors.o:	CMsgSetAllMotors.cpp CMsgSetAllMotors.h
CMsgSetControlMode.o:	CMsgSetControlMode.cpp CMsgSetControlMode.h
CMsgConfigurePID.o: CMsgConfigurePID.cpp CMsgConfigurePID.h
CMsgResetEncoders.o: CMsgResetEncoders.cpp CMsgResetEncoders.h
CMsgSetSpeed.o: CMsgSetSpeed.cpp CMsgSetSpeed.h
CMsgSetPosition.o: CMsgSetPosition.cpp CMsgSetPosition.h
CMsgSetMotorSpeed.o: CMsgSetMotorSpeed.cpp CMsgSetMotorSpeed.h
CMsgSetMotorPosition.o: CMsgSetMotorPosition.cpp CMsgSetMotorPosition.h
CMsgSetIO.o: CMsgSetIO.cpp CMsgSetIO.h
CMsgBase.o: CMsgBase.cpp CMsgBase.h
test_CInitSequenceFileParser.o: test_CInitSequenceFileParser.cpp
CInitSequenceFileParser.o: CInitSequenceFileParser.cpp CInitSequenceFileParser.h
test_CMsgSetIO.o: test_CMsgSetIO.cpp
