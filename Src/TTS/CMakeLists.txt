project (TTS)

add_executable ( tts
CTTS.cpp
CTTSEngine.cpp
)

target_link_libraries ( tts pthread
                            rt
                            asound
                            Runtime 
                            ControllerInterface 
                            TTSInterface 
                             
                            UCL 
                            Logger 
                            flite_cmu_us_kal 
                            flite_cmu_us_slt 
                            flite_cmu_us_awb 
                            flite_cmu_us_rms 
                            flite_usenglish 
                            flite_cmulex 
                            flite 
                            m) 
add_dependencies( tts ControllerInterface TTSInterface Runtime UCL Logger)
