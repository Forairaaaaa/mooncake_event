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

# Public component requirement
set(SIMPLE_EVENT_REQUIRES
)

# Private component requirement
set(SIMPLE_EVENT_PRIV_REQUIRES
)

# Register component
idf_component_register(
    SRCS ${SIMPLE_EVENT_SRCS}
    INCLUDE_DIRS ${SIMPLE_EVENT_INCS}
    REQUIRES ${SIMPLE_EVENT_REQUIRES}
    PRIV_REQUIRES ${SIMPLE_EVENT_PRIV_REQUIRES}
)