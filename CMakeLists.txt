cmake_minimum_required (VERSION 2.8.11 FATAL_ERROR)
project (CSE423 CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

INCLUDE(CheckIncludeFileCXX)

set(CMAKE_CXX_FLAGS "-Wall -g -O3")

## If we have other folders (move everything into a lib/ folder, etc) this adds it to the CMake search path for .h
#include_directories(${PROJECT_SOURCE_DIR}/lib)

## A list of all source files in the project that should be compiled
set (SOURCES Scanner.cpp Parser.cpp)

# Taken from: https://stackoverflow.com/questions/16485546/how-to-check-in-cmake-whether-a-given-header-file-is-available-for-c-project
# Macro makes it easy to enforce a required include file
macro(CHECK_INCLUDE_FILE_CXX_ERROR INCLUDE_FILE HAVE_FILE)
    CHECK_INCLUDE_FILE_CXX(${INCLUDE_FILE} ${HAVE_FILE})
    IF(NOT ${HAVE_FILE})
        UNSET(HAVE_FILE CACHE)
        message( FATAL_ERROR "${INCLUDE_FILE} is not found" )
    ENDIF()
endmacro()

# Make sure all the include files we need are found
check_include_file_cxx_error(stdio.h HAVE_STDIO)
check_include_file_cxx_error(stdlib.h HAVE_STDLIB)
check_include_file_cxx_error(assert.h HAVE_ASSERT)
check_include_file_cxx_error(fstream HAVE_FSTREAM)
check_include_file_cxx_error(string HAVE_STRING)

# Copy the grammar definition to the build dir
configure_file(${PROJECT_SOURCE_DIR}/grammar.txt ${PROJECT_BINARY_DIR}/grammar.txt COPYONLY)

## Any libraries that get included should be added here
#set (COMPILE_LIBS )

## Best to create a library out of common files to avoid recompiling for multiple binaries.
add_library(compiler ${SOURCES})

## Creates an executable 'scanner' with all sources in ${SOURCES} and main.cpp
add_executable(scanner main.cpp)
add_executable(parser parser_main.cpp)

#add_executable(scanner ${SOURCES} main.cpp)
#add_executable(parser ${SOURCES} parser_main.cpp)

## Links the libraries with the executable
#target_link_libraries(scanner compiler ${COMPILE_LIBS})
target_link_libraries(scanner compiler)
target_link_libraries(parser compiler)

