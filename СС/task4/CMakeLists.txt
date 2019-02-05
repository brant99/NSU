cmake_minimum_required(VERSION 3.12)
project(task4)

set(CMAKE_CXX_STANDARD 14)

add_executable(task4 main.cpp CSVParser.cpp CSVParser.h PrintTuple.cpp PrintTuple.h tuple.cpp tuple.h)