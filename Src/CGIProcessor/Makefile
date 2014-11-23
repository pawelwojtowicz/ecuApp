OUTPUT= cgiprocessor
OBJ= CCGIProcessor.o CEnvironment.o CCommandFactory.o CControllerCommand.o CProxyProvider.o

include ../../DevEnv/executableSettings

LFLAGS+= -lControllerInterface -lRuntime -lUCL -lLogger -lJSON

CCGIProcessor.o	: CCGIProcessor.cpp CCGIProcessor.h
CEnvironment.o  : CEnvironment.cpp CEnvironment.h
CCommandFactory.o : CCommandFactory.cpp CCommandFactory.h
CControllerCommand.o : CControllerCommand.cpp CControllerCommand.h
CProxyProvider.o  : CProxyProvider.cpp CProxyProvider.h
