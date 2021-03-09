cmake_minimum_required(VERSION 3.16.0)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_BUILD_TYPE Debug)
set (EXECUTABLE_OUTPUT_PATH "..")

# Project name
project(jvm_boss)

set(SOURCE_DIR src)
set(INCLUDE_DIR include)

set(HEADER_FILES
    ${INCLUDE_DIR}/begin.hpp
    ${INCLUDE_DIR}/file_reader.hpp
    ${INCLUDE_DIR}/read_bytes.hpp
    ${INCLUDE_DIR}/types.hpp
)

set(SOURCE_FILES
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/begin.cpp
    ${SOURCE_DIR}/file_reader.cpp
    ${SOURCE_DIR}/read_bytes.cpp
)

# Executable name
add_executable(jvm_boss ${DOMAINS_SOURCE_FILES}
    ${SOURCE_FILES}
)

target_include_directories(jvm_boss PUBLIC ${INCLUDE_DIR})