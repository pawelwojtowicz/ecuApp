project ( CSM_Test )

add_executable ( test_CSM
Test_CState.cpp 
Test_CArgoConfigurator.cpp 
Test_CStateMachine.cpp 
Test_CActionFactory.cpp )


add_dependencies ( test_CSM ${GTEST_LIBRARIES} UCL Logger CSM Configuration )
target_link_libraries ( test_CSM pthread rt ${GTEST_LIBRARIES} UCL Logger CSM Configuration )
