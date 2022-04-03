# cmake: https://blog.csdn.net/afei__/article/details/81201039
# CMake 最低版本号要求
cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(algorithm)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)   
SET(LIBRARY_OUTPUT_PATH    ${PROJECT_SOURCE_DIR}/output)

add_subdirectory(src)
add_subdirectory(test)