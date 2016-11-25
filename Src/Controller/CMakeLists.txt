project ( Controller )

SET( OUTPUT_NAME controller )

add_executable ( ${OUTPUT_NAME} 
CController.cpp
CProcessControl.cpp
CProcessHandler.cpp
CProcessInfo.cpp
CProcessManager.cpp
CSessionManager.cpp
CWatchdogManager.cpp
)

target_link_libraries ( ${OUTPUT_NAME} pthread rt UCL ControllerInterface Runtime Configuration Logger )
add_dependencies ( ${OUTPUT_NAME} UCL Runtime Configuration ControllerInterface Logger )
install( TARGETS ${OUTPUT_NAME} RUNTIME DESTINATION ${ECUAPP_RUNTIME_INSTALL_DIR} )
