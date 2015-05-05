OUTPUT= rbcgateway
OBJ= CInitSequenceFileParser.o CMsgBase.o CMsgConfigurePID.o CMsgFactory.o CMsgSetAllMotors.o CMsgSetCommMode.o CMsgSetControlMode.o CRBCGateway.o CRBCSendThread.o

include ../../DevEnv/executableSettings

LFLAGS+= -lControllerInterface -lTTSInterface -lJoystickInterface -lRuntime -lUCL -lLogger

CRBCGateway.o	: CRBCGateway.cpp CRBCGateway.h
CInitSequenceFileParser.o: CInitSequenceFileParser.cpp CInitSequenceFileParser.h 
CMsgBase.o: CMsgBase.cpp CMsgBase.h 
CMsgConfigurePID.o: CMsgConfigurePID.cpp CMsgConfigurePID.h
CMsgFactory.o: CMsgFactory.cpp CMsgFactory.h
CMsgSetAllMotors.o: CMsgSetAllMotors.cpp CMsgSetAllMotors.h
CMsgSetCommMode.o: CMsgSetCommMode.cpp CMsgSetCommMode.h 
CMsgSetControlMode.o: CMsgSetControlMode.cpp CMsgSetControlMode.h 
CRBCGateway.o: CRBCGateway.cpp CRBCGateway.h
CRBCSendThread.o: CRBCSendThread.cpp CRBCSendThread.h
