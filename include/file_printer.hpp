#ifndef __FILE_PRINTER_H__
#define __FILE_PRINTER_H__

#include "file_reader.hpp"
#include <cstring>


void print_basic_info(std::string filename, Class_File_Format class_file);

void print_cp_info_utf8(Cp_Info cp_info);
void print_cp_info_int(Cp_Info cp_info);
void print_cp_info_float(Cp_Info cp_info);
void print_cp_info_long(Cp_Info cp_info);
void print_cp_info_double(Cp_Info cp_info);
void print_cp_info_class(Class_File_Format class_file, Cp_Info cp_info);
void print_cp_info_string(Class_File_Format class_file, Cp_Info cp_info);
void print_cp_info_field(Class_File_Format class_file, Cp_Info cp_info);
void print_cp_info_method(Class_File_Format class_file, Cp_Info cp_info);

void print_constant_pool_info(Class_File_Format class_file);

#endif