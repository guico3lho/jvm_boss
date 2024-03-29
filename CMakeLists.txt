cmake_minimum_required(VERSION 3.16.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_BUILD_TYPE Debug)
set(EXECUTABLE_OUTPUT_PATH "..")

# Project name
project(jvm_boss)

set(SOURCE_DIR src)
set(INCLUDE_DIR include)
set(INSTRUCTIONS_DIR instructions)

set(HEADER_FILES
    ${INCLUDE_DIR}/types.hpp
    ${INCLUDE_DIR}/read_bytes.hpp
    ${INCLUDE_DIR}/class_file.hpp
    ${INCLUDE_DIR}/file_printer.hpp
    ${INCLUDE_DIR}/cp_info.hpp
    ${INCLUDE_DIR}/interface_info.hpp
    ${INCLUDE_DIR}/field_info.hpp
    ${INCLUDE_DIR}/method_info.hpp
    ${INCLUDE_DIR}/attribute_info.hpp
    ${INCLUDE_DIR}/stack_map_table.hpp
    ${INCLUDE_DIR}/instructions_print.hpp
    ${INCLUDE_DIR}/utils.hpp
    ${INCLUDE_DIR}/interpreter.hpp
    ${INCLUDE_DIR}/frame.hpp
    ${INCLUDE_DIR}/method_area.hpp

    ${INCLUDE_DIR}/${INSTRUCTIONS_DIR}/instructions_constant.hpp
    ${INCLUDE_DIR}/${INSTRUCTIONS_DIR}/instructions_load.hpp
    ${INCLUDE_DIR}/${INSTRUCTIONS_DIR}/instructions_store.hpp
    ${INCLUDE_DIR}/${INSTRUCTIONS_DIR}/instructions_math.hpp
    ${INCLUDE_DIR}/${INSTRUCTIONS_DIR}/instructions_stack.hpp
    ${INCLUDE_DIR}/${INSTRUCTIONS_DIR}/instructions_conversion.hpp
    ${INCLUDE_DIR}/${INSTRUCTIONS_DIR}/instructions_comparison.hpp
    ${INCLUDE_DIR}/${INSTRUCTIONS_DIR}/instructions_reference.hpp
    ${INCLUDE_DIR}/${INSTRUCTIONS_DIR}/instructions_control.hpp
    ${INCLUDE_DIR}/${INSTRUCTIONS_DIR}/instructions_extended.hpp
)

set(SOURCE_FILES
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/read_bytes.cpp
    ${SOURCE_DIR}/class_file.cpp
    ${SOURCE_DIR}/file_printer.cpp
    ${SOURCE_DIR}/cp_info.cpp
    ${SOURCE_DIR}/interface_info.cpp
    ${SOURCE_DIR}/field_info.cpp
    ${SOURCE_DIR}/method_info.cpp
    ${SOURCE_DIR}/attribute_info.cpp
    ${SOURCE_DIR}/instructions_print.cpp
    ${SOURCE_DIR}/utils.cpp
    ${SOURCE_DIR}/interpreter.cpp
    ${SOURCE_DIR}/frame.cpp
    ${SOURCE_DIR}/method_area.cpp
    ${SOURCE_DIR}/${INSTRUCTIONS_DIR}/instructions_constant.cpp
    ${SOURCE_DIR}/${INSTRUCTIONS_DIR}/instructions_load.cpp
    ${SOURCE_DIR}/${INSTRUCTIONS_DIR}/instructions_store.cpp
    ${SOURCE_DIR}/${INSTRUCTIONS_DIR}/instructions_math.cpp
    ${SOURCE_DIR}/${INSTRUCTIONS_DIR}/instructions_stack.cpp
    ${SOURCE_DIR}/${INSTRUCTIONS_DIR}/instructions_conversion.cpp
    ${SOURCE_DIR}/${INSTRUCTIONS_DIR}/instructions_comparison.cpp
    ${SOURCE_DIR}/${INSTRUCTIONS_DIR}/instructions_reference.cpp
    ${SOURCE_DIR}/${INSTRUCTIONS_DIR}/instructions_control.cpp
    ${SOURCE_DIR}/${INSTRUCTIONS_DIR}/instructions_extended.cpp
)

# Executable name
add_executable(jvm_boss ${DOMAINS_SOURCE_FILES}
    ${SOURCE_FILES}
)

target_include_directories(jvm_boss PUBLIC ${INCLUDE_DIR})