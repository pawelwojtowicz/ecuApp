project ( Controller )


add_executable ( controller 
CController.cpp
CProcessControl.cpp
CProcessHandler.cpp
CProcessInfo.cpp
CProcessManager.cpp
CSessionManager.cpp
CWatchdogManager.cpp
)

target_link_libraries ( controller pthread rt UCL ControllerInterface Runtime Configuration Logger )
add_dependencies ( controller UCL Runtime Configuration ControllerInterface Logger )