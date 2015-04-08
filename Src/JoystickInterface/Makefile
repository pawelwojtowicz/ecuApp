OUTPUT= libJoystickInterface
OBJ = CJoyState.o CJoystickProxy.o CJoystickStub.o

include ../../DevEnv/staticLibSettings

LFLAGS+= -lRuntime

CJoyState.o: CJoyState.cpp CJoyState.h
CJoystickProxy.o: CJoystickProxy.cpp CJoystickProxy.h
CJoystickStub.o: CJoystickStub.cpp CJoystickStub.h 

