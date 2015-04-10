OUTPUT=test_Joystick
OBJ=test_CJoystate.o CJoyState.o
VPATH=$(SUBJ_PATH)/JoystickInterface

include ../../DevEnv/unitTestSettings

LFLAGS+= -lUCL -lrt

test_CJoystate.o:	test_CJoystate.cpp
CJoyState.o: CJoyState.cpp CJoyState.h
