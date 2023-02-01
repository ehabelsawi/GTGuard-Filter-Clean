set(SOURCE_FILES
        src/SRIFLib/NInterfaceResource.cpp src/SRIFLib/NInterfaceResource.h)

add_library(SROInterfaceLIB STATIC ${SOURCE_FILES})
target_include_directories(SROInterfaceLIB
        PUBLIC src/)
target_link_libraries(SROInterfaceLIB
        BSLib
        GFXFileManagerLIB
        abi-testing
        )
