OUTPUT= cgiprocessor
OBJ= CCGIProcessor.o CEnvironment.o CActionFactory.o CControllerAction.o CProxyProvider.o CGetMemInfoAction.o

include ../../DevEnv/executableSettings

LFLAGS+= -lControllerInterface -lRuntime -lUCL -lLogger -lJSON

CCGIProcessor.o	: CCGIProcessor.cpp CCGIProcessor.h
CEnvironment.o  : CEnvironment.cpp CEnvironment.h
CActionFactory.o : CActionFactory.cpp CActionFactory.h
CControllerAction.o : CControllerAction.cpp CControllerAction.h
CProxyProvider.o  : CProxyProvider.cpp CProxyProvider.h
CGetMemInfoAction.o: CGetMemInfoAction.cpp CGetMemInfoAction.h
