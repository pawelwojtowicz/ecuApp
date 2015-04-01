OUTPUT= joystick
OBJ= CJoystick.o CInputHandler.o

include ../../DevEnv/executableSettings

LFLAGS+= -lControllerInterface -lRuntime -lUCL -lLogger -lSDL
CFLAGS+= -I"/usr/local/include"

CJoystick.o	: CJoystick.cpp CJoystick.h
CInputHandler.o: CInputHandler.cpp CInputHandler.h
