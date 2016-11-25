project (UCLTest )

SET ( UCL_SRC_DIR  ${ECUAPP_SRC}/UCL )

add_definitions( -DUNIT_TEST ) 

add_executable ( test_UCL 
CTest_SerialPort.cpp
CTest_Tokenizer.cpp
CTest_CSocket.cpp
CTest_CSerializable.cpp
${UCL_SRC_DIR}/CSerializable.cpp
CTest_CMemoryInfo.cpp
)

add_dependencies ( test_UCL ${GTEST_LIBRARIES} Configuration Logger UCL)
target_link_libraries ( test_UCL pthread ${GTEST_LIBRARIES} Configuration Logger UCL rt )
