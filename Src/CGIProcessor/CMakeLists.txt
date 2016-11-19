project ( CGIProcessor )

SET( OUTPUT_NAME cgiprocessor )

add_executable( ${OUTPUT_NAME}
CCGIProcessor.cpp
CEnvironment.cpp
CActionFactory.cpp
CControllerAction.cpp
CProxyProvider.cpp
CGetMemInfoAction.cpp
)

target_link_libraries ( ${OUTPUT_NAME} pthread rt ControllerInterface Runtime UCL Logger JSON )
add_dependencies ( ${OUTPUT_NAME} ControllerInterface Runtime UCL Logger JSON )
install( TARGETS ${OUTPUT_NAME} RUNTIME DESTINATION ${ECUAPP_RUNTIME_INSTALL_DIR} )

if ( DEFINED ECUAPP_INSTALL_ROOT)
	install	( CODE "
									EXECUTE_PROCESS	(
																	COMMAND ln -s ${CMAKE_INSTALL_PREFIX}/bin/${OUTPUT_NAME} ${ECUAPP_INSTALL_ROOT}/srv/www/cgi-bin/controller
																	)
								 "
					)
else ()
	message (WARNING "ECUAPP_INSTALL_ROOT not defined - it's required to set up the symboling link to ${OUTPUT_NAME} during the installation")
endif()
