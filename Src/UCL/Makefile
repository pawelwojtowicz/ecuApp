OUTPUT= libUCL.so
OBJ= FileSystem.o CTokenizer.o CFile.o CThread.o

include ../../DevEnv/commonSettings
include ../../DevEnv/sharedLibSettings
include ../../DevEnv/buildingRules
	

FileSystem.o:	FileSystem.cpp FileSystem.h
CTokenizer.o:	CTokenizer.cpp CTokenizer.h
CFile.o:	CFile.h CFile.cpp
CThread.o:	CThread.h CThread.cpp

clean:
	-rm $(OBJ_DIR)/*.o
	-rm $(INSTALL_PATH)/$(OUTPUT)

