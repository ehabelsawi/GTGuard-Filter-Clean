set(SOURCE_FILES
        src/SRIFLib/NInterfaceResource.cpp src/SRIFLib/NInterfaceResource.h
        src/SRIFLib/GNFontChar.h
        src/SRIFLib/NGFontTexture.cpp src/SRIFLib/NGFontTexture.h
        src/SRIFLib/NIFTextBoard.cpp src/SRIFLib/NIFTextBoard.h)

add_library(SROInterfaceLIB STATIC ${SOURCE_FILES})
target_include_directories(SROInterfaceLIB PUBLIC
        src/
        ${DirectX_INCLUDE_DIRS})
target_link_libraries(SROInterfaceLIB
        BSLib
        GFXFileManagerLIB
        abi-testing
        ${DirectX_LIBRARIES}
        )
target_link_directories(SROInterfaceLIB PUBLIC ${DirectX_LIBRARY_PATHS})
