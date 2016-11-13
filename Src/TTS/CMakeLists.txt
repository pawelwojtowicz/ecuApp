project (TTS)

add_executable ( tts
CTTS.cpp
CTTSEngine.cpp
)

SET ( TTS_DEPENDENCIES  pthread rt Runtime ControllerInterface TTSInterface UCL Logger flite_cmu_us_kal flite_cmu_us_slt flite_cmu_us_awb flite_cmu_us_rms flite_usenglish flite_cmulex flite m )

if ( CMAKE_CROSSCOMPILING )
  # add asound in case of cross compiling
  SET (TTS_DEPENDENCIES asound ${TTS_DEPENDENCIES} )
endif ()

target_link_libraries ( tts ${TTS_DEPENDENCIES} )
add_dependencies( tts ControllerInterface TTSInterface Runtime UCL Logger)
