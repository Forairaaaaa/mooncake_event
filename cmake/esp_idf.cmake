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

# Public component requirement
set(MOONCAKE_EVENT_REQUIRES
)

# Private component requirement
set(MOONCAKE_EVENT_PRIV_REQUIRES
)

# Register component
idf_component_register(
    SRCS ${MOONCAKE_EVENT_SRCS}
    INCLUDE_DIRS ${MOONCAKE_EVENT_INCS}
    REQUIRES ${MOONCAKE_EVENT_REQUIRES}
    PRIV_REQUIRES ${MOONCAKE_EVENT_PRIV_REQUIRES}
)