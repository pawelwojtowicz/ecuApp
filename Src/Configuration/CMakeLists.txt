project ( Configuration )


SET( OUTPUT_NAME Configuration )

add_library ( ${OUTPUT_NAME} SHARED
CConfiguration.cpp
CConfigNode.cpp
CParameter.cpp
)

target_link_libraries ( ${OUTPUT_NAME} UCL XMLParser )
add_dependencies ( ${OUTPUT_NAME} UCL XMLParser )
install ( TARGETS ${OUTPUT_NAME} LIBRARY DESTINATION ${ECUAPP_LIBRARY_INSTALL_DIR} )
