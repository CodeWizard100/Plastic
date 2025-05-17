cmake_minimum_required(VERSION 3.16)
project(Plastic)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

option(BUILD_AS_EXECUTABLE "Build targets as executables instead of libraries" ON)

add_subdirectory(Plastic_shared)

file(GLOB children RELATIVE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/Plastic_*)
foreach(child ${children})
    if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/${child} AND NOT ${child} STREQUAL "Plastic_shared")
        add_subdirectory(${child})
    endif()
endforeach()
