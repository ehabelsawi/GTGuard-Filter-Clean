add_library(GFXMainFrame STATIC)

target_sources(GFXMainFrame PRIVATE
        src/GFXMainFrame/GFXMainFrame.cpp
        src/GFXMainFrame/GWnd.cpp
        src/GFXMainFrame/GWndBase.cpp
        src/GFXMainFrame/Process.cpp
        src/GFXMainFrame/Camera.cpp
        src/GFXMainFrame/Controler.cpp
)

target_include_directories(GFXMainFrame
        PUBLIC
        src/
        ${DirectX_INCLUDE_DIRS})
target_link_libraries(GFXMainFrame BSLib support d3d9)
