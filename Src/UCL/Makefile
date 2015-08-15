OUTPUT= libUCL
OBJ= SystemEnvironment.o FileSystem.o CTokenizer.o CFile.o CThread.o CSerialPort.o CUnixDomainSocket.o CSerializable.o CSharedMemory.o CSemaphore.o CMemoryInfo.o CFastHash.o

include ../../DevEnv/sharedLibSettings

FileSystem.o:	FileSystem.cpp FileSystem.h
CSharedMemory.o: CSharedMemory.cpp CSharedMemory.h
CTokenizer.o:	CTokenizer.cpp CTokenizer.h
CFile.o:	CFile.h CFile.cpp
CThread.o:	CThread.h CThread.cpp
SystemEnvironment.o: SystemEnvironment.cpp SystemEnvironment.h
CSerialPort.o:	CSerialPort.cpp CSerialPort.h
CUnixDomainSocket.o:	CUnixDomainSocket.h CUnixDomainSocket.cpp
CSerializable.o: CSerializable.cpp CSerializable.h
CSemaphore.o: CSemaphore.cpp CSemaphore.h
CMemoryInfo.o: CMemoryInfo.cpp CMemoryInfo.h CPROCInfoParserBase.h
CFastHash.o: CFastHash.cpp CFastHash.h
