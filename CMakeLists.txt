cmake_minimum_required (VERSION 2.8.11 FATAL_ERROR)
project (CSE423 C CXX)

INCLUDE(CheckIncludeFiles)
INCLUDE(CheckIncludeFileCXX)

## If we have other folders (move everything into a lib/ folder, etc) this adds it to the CMake search path for .h
#include_directories(${PROJECT_SOURCE_DIR}/lib)

## A list of all source files in the project that should be compiled
set (SOURCES Scanner.cpp)

## Any libraries that get included should be added here
#set (COMPILE_LIBS )

## Creates an executable 'scanner' with all sources in ${SOURCES} and main.cpp
add_executable(scanner ${SOURCES} main.cpp)

## Links the libraries with the executable
#target_link_libraries(scanner ${COMPILE_LIBS})
