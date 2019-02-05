cmake_minimum_required(VERSION 3.12)
project(task3)

set(CMAKE_CXX_STANDARD 14)

file(GLOB GamerType_source GamerType/*.cpp)
file(GLOB GamerType_head GamerType/*.h)
file(GLOB ViewType_source ViewType/*.cpp)
file(GLOB ViewType_head ViewType/*.h)
file(GLOB source *.cpp)
file(GLOB head *.h)

add_executable(task3 ${source} ${GamerType_source} ${ViewType_source} ${head} ${GamerType_head} ${ViewType_head} Controller.cpp Controller.h Factory.cpp Factory.h Maker.h BattleShipEx.h)
include_directories(GamerType ViewType)
