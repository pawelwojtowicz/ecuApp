OUTPUT= libCSM
OBJ= CState.o CTransition.o CArgoConfigurator.o CStateMachine.o CActionFactory.o

include ../../DevEnv/sharedLibSettings

LFLAGS+= -lXMLParser -lUCL

CStateMachine.o: CStateMachine.cpp CStateMachine.h
CState.o:	CState.cpp CState.h
CTransition.o: CTransition.cpp CTransition.h
CArgoConfigurator.o: CArgoConfigurator.cpp CArgoConfigurator.h
CActionFactory.o: CActionFactory.cpp CActionFactory.h
