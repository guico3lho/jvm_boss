cmake_minimum_required(VERSION 3.16.0)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_BUILD_TYPE Debug)
set (EXECUTABLE_OUTPUT_PATH "..")

# Project name
project(jvm_boss)

set(SOURCE_DIR src)
set(INCLUDE_DIR include)

set(HEADER_FILES
    ${INCLUDE_DIR}/types.hpp
    ${INCLUDE_DIR}/Types.h
    ${INCLUDE_DIR}/Class_File.h
    ${INCLUDE_DIR}/Cp_Info.h
    ${INCLUDE_DIR}/FileDealer.h
    
)

set(SOURCE_FILES
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/Class_File.cpp
    ${SOURCE_DIR}/ConstantClasses.cpp
    ${SOURCE_DIR}/FileDealer.cpp
)

# Executable name
add_executable(jvm_boss ${DOMAINS_SOURCE_FILES}
    ${SOURCE_FILES}
)

target_include_directories(jvm_boss PUBLIC ${INCLUDE_DIR})