project ( ControllerInterface )

add_library ( ControllerInterface STATIC

CControllerProxy.cpp
CControllerStub.cpp
CPublicProcessInfo.cpp
)

target_link_libraries ( ControllerInterface Runtime )
add_dependencies ( ControllerInterface Runtime )