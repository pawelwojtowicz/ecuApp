OUTPUT= tts
OBJ= CTTS.o CTTSEngine.o

include ../../DevEnv/executableSettings

LFLAGS+= -lControllerInterface -lTTSInterface -lRuntime -lUCL -lLogger -lflite_cmu_us_kal -lflite_cmu_us_slt -lflite_cmu_us_awb -lflite_cmu_us_rms -lflite_usenglish -lflite_cmulex -lflite -lm

CTTS.o	: CTTS.cpp CTTS.h
CTTSEngine.o	: CTTSEngine.cpp CTTSEngine.h
