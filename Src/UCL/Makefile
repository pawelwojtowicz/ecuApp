include ../../DevEnv/commonSettings
include ../../DevEnv/sharedLibSettings

OUTPUT= libUCL.so
LINKER_INPUT= FileSystem.o CTokenizer.o CFile.o CThread.o 

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

default: $(LINKER_INPUT)
	-mkdir $(INSTALL_PATH)
	$(CC) $(LFLAGS) -o $(INSTALL_PATH)/$(OUTPUT) $(LINKER_INPUT)
	

FileSystem.o:	FileSystem.cpp FileSystem.h
CTokenizer.o:	CTokenizer.cpp CTokenizer.h
CFile.o:	CFile.h CFile.cpp
CThread.o:	CThread.h CThread.cpp

clean:
	-rm *.o
	-rm $(INSTALL_PATH)/$(OUTPUT)

