project ( ControllerUnitTests )

SET ( CONTROLLER_SRC_DIR ${ECU_APP_SRC}/Controller)

add_executable ( testController
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

target_link_libraries ( testController ${GTEST_LIBRARIES} UCL Configuration Logger )
add_dependencies ( testController ${GTEST_LIBRARIES} UCL Configuration Logger )