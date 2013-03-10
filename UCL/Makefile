CC=g++
FLAGS= -c -Wall -pedantic -fPIC
OUTPUT= libUCL.so
OBJECT_INPUT= FileSystem.o
INSTALL_PATH=_install

.cpp.o:
	$(CC) $(FLAGS) $< -o $@


default: FileSystem.o CFile.o
	mkdir $(INSTALL_PATH)
	$(CC) -shared -o $(INSTALL_PATH)/$(OUTPUT) *.o
	

FileSystem.o: FileSystem.cpp FileSystem.h
CFile.o:	CFile.h CFile.cpp

clean:
	rm *.o
	rm $(INSTALL_PATH)/*.*
	rmdir $(INSTALL_PATH)

