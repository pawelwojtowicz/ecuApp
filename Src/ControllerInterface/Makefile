OUTPUT= libControllerInterface
OBJ = CControllerProxy.o CControllerStub.o CPublicProcessInfo.o

include ../../DevEnv/staticLibSettings

LFLAGS+= -lRuntime

CControllerProxy.o: CControllerProxy.cpp CControllerProxy.h
CControllerStub.o: CControllerStub.cpp CControllerStub.h
CPublicProcessInfo.o: CPublicProcessInfo.cpp CPublicProcessInfo.h

