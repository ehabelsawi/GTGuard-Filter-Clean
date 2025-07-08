add_library(NavMesh STATIC)

target_sources(NavMesh PRIVATE
        src/RTNavMeshTerrain.cpp
)

target_include_directories(NavMesh
        PUBLIC
        include/
        ${DirectX_INCLUDE_DIRS}
        PRIVATE include/NavMesh)

target_link_libraries(NavMesh d3d9)
