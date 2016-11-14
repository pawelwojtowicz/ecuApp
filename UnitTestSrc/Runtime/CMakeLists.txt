project (Runtime )

SET ( RUNTIME_SRC_DIR  ${ECUAPP_SRC}/Runtime ) 

add_executable ( test_Runtime 
${RUNTIME_SRC_DIR}/CMessage.cpp
${RUNTIME_SRC_DIR}/CMessenger.cpp
CTest_Messenger.cpp
CUDSMockHelper.cpp
CSubscriberMock.cpp
CTest_CSharedStorage.cpp
${RUNTIME_SRC_DIR}/CSharedStorage.cpp
)

add_dependencies ( test_Runtime ${GTEST_LIBRARIES} Configuration Logger UCL)
target_link_libraries ( test_Runtime pthread ${GTEST_LIBRARIES} Configuration Logger UCL rt )
