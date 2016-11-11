project ( Logger )

add_library( Logger SHARED
CConsoleTarget.cpp
CLoggingAgent.cpp
CLogManager.cpp
CLogMsg.cpp
CSyslogTarget.cpp
)

target_link_libraries ( Logger Configuration )
add_dependencies (Logger Configuration )