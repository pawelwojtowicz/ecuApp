project ( Example )

SET( OUTPUT_NAME exampleApp )

add_executable ( ${OUTPUT_NAME}
CExampleApp.cpp
)

target_link_libraries ( ${OUTPUT_NAME} ControllerInterface Runtime rt Configuration pthread TTSInterface  UCL Logger ) 
add_dependencies ( ${OUTPUT_NAME} Configuration Logger ControllerInterface TTSInterface Runtime UCL Logger )
install ( TARGETS ${OUTPUT_NAME} RUNTIME DESTINATION ${ECUAPP_RUNTIME_INSTALL_DIR} )
