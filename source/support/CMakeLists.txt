set(SOURCE_FILES src/hook.cpp)

add_library(support STATIC ${SOURCE_FILES})
target_include_directories(support
        PUBLIC include
        PRIVATE include/support)
