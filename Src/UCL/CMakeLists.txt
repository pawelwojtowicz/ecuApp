project (UCL)

SET(OUTPUT_NAME UCL )

add_library( ${OUTPUT_NAME} SHARED 
CFastHash.cpp
CFile.cpp
CMemoryInfo.cpp
CSemaphore.cpp
CSerializable.cpp
CSerialPort.cpp
CSharedMemory.cpp 
CThread.cpp
CTokenizer.cpp
CUnixDomainSocket.cpp
FileSystem.cpp
SystemEnvironment.cpp
)

install ( TARGETS ${OUTPUT_NAME} LIBRARY DESTINATION ${ECUAPP_LIBRARY_INSTALL_DIR} )
