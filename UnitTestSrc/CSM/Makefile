OUTPUT=test_CSM
OBJ=Test_CState.o Test_CArgoConfigurator.o Test_CStateMachine.o Test_CActionFactory.o

VPATH=$(SUBJ_PATH)/CSM

include ../../DevEnv/unitTestSettings

LFLAGS+= -lrt -lUCL -lLogger -lCSM -lConfiguration

Test_CState.o: Test_CState.cpp
Test_CArgoConfigurator.o: Test_CArgoConfigurator.cpp
Test_CActionFactory.o: Test_CActionFactory.cpp
Test_CStateMachine.o: Test_CStateMachine.cpp

