project ( ControllerUnitTests )

SET ( CONTROLLER_SRC_DIR ${ECUAPP_SRC}/Controller)

add_executable ( test_Controller
${CONTROLLER_SRC_DIR}/CProcessInfo.cpp
${CONTROLLER_SRC_DIR}/CProcessHandler.cpp
${CONTROLLER_SRC_DIR}/CSessionManager.cpp
${CONTROLLER_SRC_DIR}/CProcessManager.cpp
${CONTROLLER_SRC_DIR}/CProcessControl.cpp
CTest_CProcessManager.cpp
CTest_CSessionManager_Logic.cpp
CTest_CSessionManager_Helpers.cpp
CTest_Controller.cpp
)

target_link_libraries ( test_Controller ${GTEST_LIBRARIES} rt UCL Configuration Logger Runtime ControllerInterface  )
add_dependencies ( test_Controller ${GTEST_LIBRARIES} UCL Configuration Logger Runtime ControllerInterface )
