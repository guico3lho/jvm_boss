#ifndef __FILE_PRINTER_H__
#define __FILE_PRINTER_H__

#include "file_reader.hpp"
#include <cstring>


void print_basic_info(std::string filename, Class_File_Format class_file);

void print_cp_info_utf8(Class_File_Format class_file);

void print_constant_pool_info(Class_File_Format class_file);

#endif