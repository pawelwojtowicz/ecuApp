project ( Logger )

SET( OUTPUT_NAME Logger )

add_library( ${OUTPUT_NAME} SHARED
CConsoleTarget.cpp
CLoggingAgent.cpp
CLogManager.cpp
CLogMsg.cpp
CSyslogTarget.cpp
)

target_link_libraries ( ${OUTPUT_NAME} Configuration )
add_dependencies (${OUTPUT_NAME} Configuration )
install ( TARGETS ${OUTPUT_NAME} LIBRARY DESTINATION ${ECUAPP_LIBRARY_INSTALL_DIR} )
