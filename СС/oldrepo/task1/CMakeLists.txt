cmake_minimum_required(VERSION 3.12)
project(task1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x -Wall")

set(source main.cpp)
add_executable(task1 ${source})

include_directories(TritSet)

add_subdirectory(TritSet)
add_subdirectory(Tests)

target_link_libraries(task1 TritSet)