project (TTS)

SET( OUTPUT_NAME tts )

add_executable ( ${OUTPUT_NAME}
CTTS.cpp
CTTSEngine.cpp
)

SET ( TTS_DEPENDENCIES  pthread rt Runtime ControllerInterface TTSInterface UCL Logger flite_cmu_us_kal flite_cmu_us_slt flite_cmu_us_awb flite_cmu_us_rms flite_usenglish flite_cmulex flite m )

if ( CMAKE_CROSSCOMPILING )
  # add asound in case of cross compiling
  SET (TTS_DEPENDENCIES asound ${TTS_DEPENDENCIES} )
endif ()

target_link_libraries ( ${OUTPUT_NAME} ${TTS_DEPENDENCIES} )
add_dependencies( ${OUTPUT_NAME} ControllerInterface TTSInterface Runtime UCL Logger)
install ( TARGETS ${OUTPUT_NAME} RUNTIME DESTINATION ${ECUAPP_RUNTIME_INSTALL_DIR} )
