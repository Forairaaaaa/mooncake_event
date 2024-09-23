project(mooncake_event)

# Src files
file(GLOB_RECURSE MOONCAKE_EVENT_SRCS
    ${MOONCAKE_EVENT_ROOT_DIR}/src/*.c
    ${MOONCAKE_EVENT_ROOT_DIR}/src/*.cpp
)
# Include
set(MOONCAKE_EVENT_INCS
    ${MOONCAKE_EVENT_ROOT_DIR}/src/
    ${MOONCAKE_EVENT_ROOT_DIR}/src/spdlog/include/
)


add_library(${PROJECT_NAME} ${MOONCAKE_EVENT_SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC ${MOONCAKE_EVENT_INCS})


option(MOONCAKE_EVENT_BUILD_EXAMPLE "Build example" ON)


# Example
if(MOONCAKE_EVENT_BUILD_EXAMPLE)
    add_subdirectory(./example/)
endif()

# CTest
enable_testing()
add_test(basic example/basic)
add_test(singleton example/singleton)
add_test(start_and_stop example/start_and_stop)
