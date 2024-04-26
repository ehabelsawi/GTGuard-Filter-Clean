set(SOURCE_FILES src/hook.cpp)

add_library(hook STATIC ${SOURCE_FILES})
target_include_directories(hook
        PUBLIC include/
        PRIVATE include/hook)
