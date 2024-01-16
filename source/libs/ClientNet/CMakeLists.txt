add_library(ClientNet STATIC)

target_sources(ClientNet PRIVATE
        src/ClientNet/MsgStreamBuffer.h
        src/ClientNet/MsgStreamBuffer.cpp
        src/ClientNet/IClientNet.h
        src/ClientNet/ClientNet.h
        src/ClientNet/ClientNet.cpp
)

target_link_libraries(ClientNet PUBLIC BSLib abi-testing remodel)
target_include_directories(ClientNet PUBLIC src/)
