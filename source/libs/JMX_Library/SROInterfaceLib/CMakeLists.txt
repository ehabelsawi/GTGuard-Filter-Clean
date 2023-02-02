set(SOURCE_FILES
        src/SRIFLib/NInterfaceResource.cpp src/SRIFLib/NInterfaceResource.h
        src/SRIFLib/GNFontChar.h
        src/SRIFLib/NGFontTexture.cpp src/SRIFLib/NGFontTexture.h
        src/SRIFLib/NIFTextBoard.cpp src/SRIFLib/NIFTextBoard.h)

add_library(SROInterfaceLIB STATIC ${SOURCE_FILES})
target_include_directories(SROInterfaceLIB PUBLIC src/)
target_link_libraries(SROInterfaceLIB
        BSLib
        GFXFileManagerLIB
        GFX3DFunction
        abi-testing
        )
