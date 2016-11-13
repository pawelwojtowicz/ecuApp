project ( Example )

add_executable ( exampleApp
CExampleApp.cpp
)

target_link_libraries ( exampleApp ControllerInterface Runtime rt Configuration pthread TTSInterface  UCL Logger ) 
add_dependencies ( exampleApp Configuration Logger ControllerInterface TTSInterface Runtime UCL Logger )