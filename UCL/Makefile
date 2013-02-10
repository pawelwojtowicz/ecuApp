CC=g++
FLAGS= -c -Wall -pedantic -fPIC
OUTPUT= libUCL.so
OBJECT_INPUT= FileSystem.o
INSTALL_PATH=_install

default: FileSystem.o CFile.o
	mkdir $(INSTALL_PATH)
	$(CC) -shared -o $(INSTALL_PATH)/$(OUTPUT) *.o
	

FileSystem.o: FileSystem.cpp FileSystem.h
	$(CC) $(FLAGS) FileSystem.cpp -o FileSystem.o

CFile.o:	CFile.h CFile.cpp
	$(CC) $(FLAGS) CFile.cpp -o CFile.o

clean:
	rm *.o
	rm $(INSTALL_PATH)/*.*
	rmdir $(INSTALL_PATH)

