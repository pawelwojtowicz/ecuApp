project ( Example )

add_executable ( exampleApp
CExampleApp.cpp
)

target_link_libraries ( exampleApp Runtime rt Configuration pthread ControllerInterface TTSInterface  UCL Logger ) 
add_dependencies ( exampleApp Configuration Logger ControllerInterface TTSInterface Runtime UCL Logger )