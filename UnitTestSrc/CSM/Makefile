OUTPUT=test_CSM
OBJ=Test_CArgoConfigurator.o Test_CStateMachine.o

VPATH=$(SUBJ_PATH)/CSM

include ../../DevEnv/unitTestSettings

LFLAGS+= -lrt -lUCL -lLogger -lCSM -lConfiguration

Test_CArgoConfigurator.o: Test_CArgoConfigurator.cpp
Test_CStateMachine.o: Test_CStateMachine.cpp
