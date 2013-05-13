CC=g++
CFLAGS= -c -Wall -pedantic -fPIC -pthread
LFLAGS= -shared -pthread
OUTPUT= libUCL.so
INSTALL_PATH=_install

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
	-rm $(INSTALL_PATH)/*.*
	-rmdir $(INSTALL_PATH)

