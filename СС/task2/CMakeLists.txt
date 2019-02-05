cmake_minimum_required(VERSION 3.12)
project(task2)

set(CMAKE_CXX_STANDARD 17)
file(GLOB Fold_sources Commands/*.cpp)
file(GLOB Fold_head Commands/*.h)

add_executable(task2 main.cpp StackCalc.cpp  ConExecute.cpp ConExecute.h StackCalc.h ${Fold_sources} ${Fold_head} CalcEx.h)

include_directories(Commands)
add_subdirectory(Commands)
