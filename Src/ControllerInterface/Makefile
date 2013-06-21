OUTPUT= libControllerInterface
OBJ = CControllerProxy.o CControllerStub.o

include ../../DevEnv/staticLibSettings

LFLAGS+= -lRuntime

CControllerProxy.o: CControllerProxy.cpp CControllerProxy.h
CControllerStub.o: CControllerStub.cpp CControllerStub.h

