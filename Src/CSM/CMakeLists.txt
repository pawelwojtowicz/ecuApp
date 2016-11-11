project (CSM )

add_library ( CSM SHARED
CState.cpp
CTransition.cpp
CArgoConfigurator.cpp 
CStateMachine.cpp 
CActionFactory.cpp
)

target_link_libraries ( CSM UCL XMLParser )
add_dependencies (CSM UCL XMLParser )