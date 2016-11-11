project ( Configuration )

add_library ( Configuration
CConfiguration.cpp
CConfigNode.cpp
CParameter.cpp
)

target_link_libraries ( Configuration UCL XMLParser )
add_dependencies ( Configuration UCL XMLParser )