cmake_minimum_required(VERSION 2.8)
project(IPC_Driver_ShortestPath)

## Project specific configurations go here

# enable c++11 support
set (CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/run)

# create the main executable
## add additional .cpp files if needed
add_executable(shortest_path shortest_path.cpp)
add_executable(ipc_driver ipc_driver.cpp)
add_executable(rgen rgen.cpp)

# create the executable for tests
install(PROGRAMS input_parser.py street_db.py DESTINATION bin)
install(TARGETS shortest_path ipc_driver rgen RUNTIME DESTINATION bin)
