project ( CGIProcessor )

add_executable( cgiprocessor
CCGIProcessor.cpp
CEnvironment.cpp
CActionFactory.cpp
CControllerAction.cpp
CProxyProvider.cpp
CGetMemInfoAction.cpp
)

target_link_libraries ( cgiprocessor pthread rt ControllerInterface Runtime UCL Logger JSON )
add_dependencies ( cgiprocessor ControllerInterface Runtime UCL Logger JSON )