project (TTSInterface)

add_library( TTSInterface STATIC
CTTSProxy.cpp
CTTSStub.cpp
)

target_link_libraries ( TTSInterface Runtime )
add_dependencies ( TTSInterface Runtime )