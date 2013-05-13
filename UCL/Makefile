CC=g++
CFLAGS= -c -Wall -pedantic -fPIC
LFLAGS= -shared -pthread
OUTPUT= libUCL.so
OBJECT_INPUT= FileSystem.o
INSTALL_PATH=_install

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@


default: FileSystem.o CFile.o CTokenizer.o CThread.o
	-mkdir $(INSTALL_PATH)
	$(CC) $(LFLAGS) -o $(INSTALL_PATH)/$(OUTPUT) *.o
	

FileSystem.o:	FileSystem.cpp FileSystem.h
CTokenizer.o:	CTokenizer.cpp CTokenizer.h
CFile.o:	CFile.h CFile.cpp
CThread.o:	CThread.h CThread.cpp

clean:
	-rm *.o
	-rm $(INSTALL_PATH)/*.*
	-rmdir $(INSTALL_PATH)

