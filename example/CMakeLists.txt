# Basic
add_executable(basic ./basic.cpp)
target_link_libraries(basic ${PROJECT_NAME})

# Basic
add_executable(singleton ./singleton.cpp)
target_link_libraries(singleton ${PROJECT_NAME})

# Start and stop
add_executable(start_and_stop ./start_and_stop.cpp)
target_link_libraries(start_and_stop ${PROJECT_NAME})
