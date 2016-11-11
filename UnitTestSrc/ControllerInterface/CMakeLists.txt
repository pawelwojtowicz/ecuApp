project (ControllerInterfaceTest)

add_executable ( test_ControllerInterface
CTest_CPublicProcessInfo.cpp
)

target_link_libraries ( test_ControllerInterface ${GTEST_LIBRARIES} rt Configuration Logger UCL Runtime ControllerInterface )
add_dependencies ( test_ControllerInterface ${GTEST_LIBRARIES} Configuration Logger UCL Runtime ControllerInterface)