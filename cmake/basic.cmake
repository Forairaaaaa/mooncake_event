project(simple_event)

# Src files
file(GLOB_RECURSE SIMPLE_EVENT_SRCS
    ${SIMPLE_EVENT_ROOT_DIR}/src/*.c
    ${SIMPLE_EVENT_ROOT_DIR}/src/*.cpp
)
# Include
set(SIMPLE_EVENT_INCS
    ${SIMPLE_EVENT_ROOT_DIR}/src/
    ${SIMPLE_EVENT_ROOT_DIR}/src/spdlog/include/
)


add_library(${PROJECT_NAME} ${SIMPLE_EVENT_SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC ${SIMPLE_EVENT_INCS})


option(SIMPLE_EVENT_BUILD_EXAMPLE "Build example" ON)


# Example
if(SIMPLE_EVENT_BUILD_EXAMPLE)
    add_subdirectory(./example/)
endif()

# CTest
enable_testing()
add_test(simple_event_basic example/simple_event_basic)
