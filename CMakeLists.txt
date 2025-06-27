cmake_minimum_required(VERSION 3.12)
project(SRO_DevKit)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include(cmake/CPM.cmake)

set(DirectX_ROOT ${CMAKE_SOURCE_DIR}/source/third-party/)
find_package(DirectX)

if (NOT DirectX_FOUND)
    message(FATAL_ERROR "DirectX was NOT found. DevKit can not be used without it. Make sure you checked out all submodules.")
endif ()

message(STATUS "Downloading dependencies in the background ... please be patient ...")
CPMAddPackage("https://github.com/ocornut/imgui.git@1.67")
if(imgui_ADDED)
    add_library(imgui STATIC)
    target_sources(imgui
            PUBLIC
            ${imgui_SOURCE_DIR}/imgui.cpp
            ${imgui_SOURCE_DIR}/imgui_widgets.cpp
            ${imgui_SOURCE_DIR}/imgui_draw.cpp
            ${imgui_SOURCE_DIR}/examples/imgui_impl_dx9.cpp
            ${imgui_SOURCE_DIR}/examples/imgui_impl_win32.cpp
    )

    target_include_directories(imgui
            PUBLIC ${imgui_SOURCE_DIR}
    )

    target_link_libraries(imgui d3d9)

    add_executable(imgui-demo-win32-dx9)
    target_sources(imgui-demo-win32-dx9
            PUBLIC
            ${imgui_SOURCE_DIR}/examples/example_win32_directx9/main.cpp
            ${imgui_SOURCE_DIR}/imgui_demo.cpp
    )

    target_include_directories(imgui-demo-win32-dx9
            PRIVATE
            ${imgui_SOURCE_DIR}/examples/)

    target_link_libraries(imgui-demo-win32-dx9 imgui)

endif()

include(DevKit)

devkit_enforce_static_linking()
devkit_enforce_include_path()

find_package(CxxTest)
if (CXXTEST_FOUND)
    message(STATUS "CxxTest found. Testing enabled!")
    include_directories(${CXXTEST_INCLUDE_DIR})
    enable_testing()
endif ()

# We are no idiots, ignore these stupid deprecations!
add_compile_definitions(_CRT_SECURE_NO_DEPRECATE _CRT_NON_CONFORMING_SWPRINTFS)

# Set target platform ... to ... Windows XP ... oops
add_definitions(-DWINVER=0x0500)
add_definitions(-D_WIN32_WINNT=0x0500)

include(Options)

# Set loglevel if supplied as parameter
if (DEFINED PUT_LOGLEVEL)
    message(STATUS "Loglevel: ${PUT_LOGLEVEL}")
    add_definitions(-DPUT_LOGLEVEL=${PUT_LOGLEVEL})
endif ()

add_subdirectory(source)
