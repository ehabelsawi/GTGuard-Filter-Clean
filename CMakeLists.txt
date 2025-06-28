cmake_minimum_required(VERSION 3.12)
project(SRO_DevKit)

include(cmake/Options.cmake)
include(cmake/CPM.cmake)

message(STATUS "Downloading dependencies in the background ... please be patient ...")
CPMAddPackage(
    NAME dxsdk9b-minimal
    URL "https://gitlab.com/florian0/dxsdk9b-minimal/-/archive/v1/dxsdk9b-minimal-v1.zip"
    URL_HASH "SHA256=02cd5961f90b83b716e7238ae0133e6c22c59860efb770872c70f8683af43522"
)

if (dxsdk9b-minimal_ADDED)
    add_library(d3d9 INTERFACE)
    target_include_directories(d3d9 INTERFACE ${dxsdk9b-minimal_SOURCE_DIR}/Include)
    target_link_directories(d3d9 INTERFACE ${dxsdk9b-minimal_SOURCE_DIR}/Lib)
    target_link_libraries(d3d9 INTERFACE d3d9.lib)

    add_library(d3dx9 INTERFACE)
    target_include_directories(d3dx9 INTERFACE ${dxsdk9b-minimal_SOURCE_DIR}/Include)
    target_link_directories(d3dx9 INTERFACE ${dxsdk9b-minimal_SOURCE_DIR}/Lib)
    target_link_libraries(d3dx9 INTERFACE d3dx9.lib)
endif ()

if (CONFIG_IMGUI)
    CPMAddPackage(
        NAME imgui
        URL "https://github.com/ocornut/imgui/archive/refs/tags/v1.67.zip"
        URL_HASH "SHA256=556712944dee7b3489706e19635acabc0b0192c8c99b936359af7fddd17b2c44"
    )
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
endif ()


if (ENABLE_TESTING)
    CPMAddPackage(
        NAME cxxtest
        URL "https://github.com/CxxTest/cxxtest/releases/download/4.4/cxxtest-4.4.zip"
        URL_HASH "SHA256=202d62c07822672138944db5fa8b7648d598836a88f213f09790fdbb221e2011"
    )
    if (cxxtest_ADDED)
        # Help find_package to find the sources
        set(CxxTest_ROOT ${cxxtest_SOURCE_DIR})
        find_package(CxxTest)
        if (CXXTEST_FOUND)
            message(STATUS "CxxTest found. Testing enabled!")
            include_directories(${CXXTEST_INCLUDE_DIR})
            enable_testing()
        endif ()
    endif ()
endif ()

include(cmake/DevKit.cmake)

devkit_enforce_static_linking()
devkit_enforce_include_path()

# We are no idiots, ignore these stupid deprecations!
add_compile_definitions(_CRT_SECURE_NO_DEPRECATE _CRT_NON_CONFORMING_SWPRINTFS)

# Set target platform ... to ... Windows XP ... oops
add_definitions(-DWINVER=0x0500)
add_definitions(-D_WIN32_WINNT=0x0500)

# Set loglevel if supplied as parameter
if (DEFINED PUT_LOGLEVEL)
    message(STATUS "Loglevel: ${PUT_LOGLEVEL}")
    add_definitions(-DPUT_LOGLEVEL=${PUT_LOGLEVEL})
endif ()

add_subdirectory(source)
