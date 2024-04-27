add_library(SROInterfaceLIB STATIC)

target_sources(SROInterfaceLIB PRIVATE
        src/SRIFLib/NInterfaceResource.cpp
        src/SRIFLib/NGFontTexture.cpp
        src/SRIFLib/NIFTextBoard.cpp
        src/SRIFLib/NIFWnd.cpp
        src/SRIFLib/NIFUnderMenuBar.cpp
        src/SRIFLib/NIFCommunityWnd.cpp
        src/SRIFLib/NIFBlockWnd.cpp
        src/SRIFLib/NIFTileWnd.cpp
        src/SRIFLib/NIFFrame.cpp
        src/SRIFLib/NIFMainFrame.cpp
)

target_include_directories(SROInterfaceLIB PUBLIC src/)
target_link_libraries(SROInterfaceLIB
        BSLib
        # at the end need to add its, shit!
        ClientLib
        GFXFileManagerLIB
        GFX3DFunction
        support
)
