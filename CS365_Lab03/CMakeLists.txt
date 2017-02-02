cmake_minimum_required(VERSION 3.6)
project(CS365_Lab03)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    integrate.c)

add_executable(CS365_Lab03 ${SOURCE_FILES})

include_directories(/usr/include/openmpi-x86_64)