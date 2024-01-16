add_library(GFXMainFrame STATIC)

target_sources(GFXMainFrame PRIVATE
        src/GFXMainFrame/EntityManager.h
        src/GFXMainFrame/GFXMainFrame.cpp src/GFXMainFrame/GFXMainFrame.h
        src/GFXMainFrame/GWnd.cpp src/GFXMainFrame/GWnd.h
        src/GFXMainFrame/GWndBase.cpp src/GFXMainFrame/GWndBase.h
        src/GFXMainFrame/Process.cpp src/GFXMainFrame/Process.h
        src/GFXMainFrame/Camera.cpp src/GFXMainFrame/Camera.h
        src/GFXMainFrame/Controler.cpp src/GFXMainFrame/Controler.h
)

target_include_directories(GFXMainFrame
        PUBLIC
        src/
        ${DirectX_INCLUDE_DIRS})
target_link_libraries(GFXMainFrame BSLib ghidra ${DirectX_LIBRARIES})
target_link_directories(GFXMainFrame PUBLIC ${DirectX_LIBRARY_PATHS})
