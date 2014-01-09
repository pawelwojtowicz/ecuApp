OUTPUT= cgiprocessor
OBJ= CCGIProcessor.o CEnvironment.o CCommandFactory.o CDummyCommand.o

include ../../DevEnv/executableSettings

LFLAGS+= -lRuntime -lUCL -lLogger

CCGIProcessor.o	: CCGIProcessor.cpp CCGIProcessor.h
CEnvironment.o  : CEnvironment.cpp CEnvironment.h
CCommandFactory.o : CCommandFactory.cpp CCommandFactory.h
CDummyCommand.o : CDummyCommand.cpp CDummyCommand.h
