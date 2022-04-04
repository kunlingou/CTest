# cmake:
# https://blog.csdn.net/afei__/article/details/81201039
# https://cmake.org/cmake/help/v2.8.8/cmake.html#opt:-Dvar:typevalue
# CMake 最低版本号要求
cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(algorithm)

add_definitions("-Wall -lpthread")

if(${CMAKE_BUILD_TYPE} MATCHES "debug")
    add_definitions("-g -D __DEBUG__ -O0")
else()
    add_definitions("-O2")
endif()

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)   
SET(LIBRARY_OUTPUT_PATH    ${PROJECT_SOURCE_DIR}/output)

add_subdirectory(src)
add_subdirectory(test)