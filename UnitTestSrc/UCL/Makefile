OUTPUT=test_UCL
OBJ=CTest_SerialPort.o CSerialPort.o CTest_Tokenizer.o CTokenizer.o CTest_CSocket.o CUnixDomainSocket.o CMemoryInfo.o CTest_CMemoryInfo.o CTest_IPAddress.o CIPAddress.o
VPATH=$(SUBJ_PATH)/UCL

LFLAGS+= -lLogger -lConfiguration -lUCL

include ../../DevEnv/unitTestSettings

CTest_SerialPort.o:	CTest_SerialPort.cpp
CTEST_Tokenizer.o:	CTest_Tokenizer.cpp
CTest_CSocket.o:	CTest_CSocket.cpp
CTest_CSerializable.o:	CTest_CSerializable.cpp
CSerializable.o: CSerializable.cpp CSerializable.h
CTest_CMemoryInfo.o: CTest_CMemoryInfo.cpp
CTest_IPAddress.o: CTest_IPAddress.cpp
CIPAddress.o: CIPAddress.cpp CIPAddress.h
