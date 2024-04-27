add_library(DevKit_DLL SHARED)
target_sources(DevKit_DLL PRIVATE
        src/DllMain.cpp
        src/hooks/Hooks.cpp
        src/hooks/GFXVideo3d_Hook.cpp
        src/hooks/WndProc_Hook.cpp
        src/hooks/CGame_Hook.cpp
        src/examples/IFflorian0.cpp
        src/examples/NIFKyuubi09.cpp
        src/imgui_windows/ImGui_Windows.cpp
        src/imgui_windows/BasicWindow.cpp
        src/imgui_windows/InterfaceDebugger.cpp
        src/imgui_windows/SoundTool.cpp
        src/imgui_windows/NavMeshTool.cpp
        src/imgui_windows/EntityExplorer.cpp
        src/imgui_windows/NotificationTool.cpp
        src/imgui_windows/AboutWindow.cpp
        src/imgui_windows/SystemMessage.cpp
        src/imgui_windows/InterfaceTree.cpp
        src/imgui_windows/ProcessViewer.cpp
        src/imgui_windows/PartyInfo.cpp
        src/imgui_windows/CharacterData.cpp
        src/imgui_windows/ItemData.cpp
        src/imgui_windows/ErrorMessageTool.cpp
        src/imgui_windows/Inventory.cpp
        src/Util.cpp
        src/QuickStart.cpp
        src/MathUtil.cpp
)

target_link_libraries(DevKit_DLL
        BSLib
        SROInterfaceLIB
        ClientLib
        MathHelpers
        support
        winmm
)

set_target_properties(DevKit_DLL
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/BinOut/${CMAKE_BUILD_TYPE}/"
        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/BinOut/${CMAKE_BUILD_TYPE}/"
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/BinOut/${CMAKE_BUILD_TYPE}/"
)
