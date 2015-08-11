OUTPUT= libCSM
OBJ= CState.o CTransition.o CArgoConfigurator.o

include ../../DevEnv/sharedLibSettings

LFLAGS+= -lXMLParser -lUCL

CState.o:	CState.cpp CState.h
CTransition.o: CTransition.cpp CTransition.h
CArgoConfigurator.o: CArgoConfigurator.cpp CArgoConfigurator.h
