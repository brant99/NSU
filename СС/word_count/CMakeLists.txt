cmake_minimum_required(VERSION 3.10)
project(word_count)

set(CMAKE_CXX_STANDARD 11)

add_executable(word_count main.cpp wordCount.h wordCount.cpp)