project (CSM )

SET( OUTPUT_NAME CSM )

add_library ( ${OUTPUT_NAME} SHARED
CState.cpp
CTransition.cpp
CArgoConfigurator.cpp 
CStateMachine.cpp 
CActionFactory.cpp
)

target_link_libraries ( ${OUTPUT_NAME} UCL XMLParser )
add_dependencies (${OUTPUT_NAME} UCL XMLParser )
install ( TARGETS ${OUTPUT_NAME} LIBRARY DESTINATION ${ECUAPP_LIBRARY_INSTALL_DIR} )
