#ifndef __FILE_PRINTER_H__
#define __FILE_PRINTER_H__

#include "class_file.hpp"
#include "instruction.hpp"
#include <cstring>

/* BASIC INFO */
void print_major_version(u2 major_version);
void check_flag(u2 access_flags, int constant_access_flag, std::string flag);
void print_access_flags(u2 access_flags);
void print_basic_info(std::string filename, Class_File class_file);

/* CONSTANT POOL */
void print_cp_info_int(Cp_Info cp_info);
void print_cp_info_float(Cp_Info cp_info);
void print_cp_info_long(Cp_Info cp_info);
void print_cp_info_double(Cp_Info cp_info);
void print_cp_info_class(Class_File class_file, Cp_Info cp_info);
void print_cp_info_string(Class_File class_file, Cp_Info cp_info);
void print_cp_info_field(Class_File class_file, Cp_Info cp_info);
void print_cp_info_method(Class_File class_file, Cp_Info cp_info);
void print_cp_info_interface_method(Class_File class_file, Cp_Info cp_info);
void print_cp_info_name_type(Class_File class_file, Cp_Info cp_info);

void print_constant_pool(Class_File class_file);

/* INTERFACES */
void print_interfaces(Class_File class_file);

/* ATTRIBUTES */
void print_code_attribute(Class_File class_file, Code_Attribute *code_attribute);
void print_constant_value_attribute(Class_File class_file, Const_Value_Attribute *const_value);
void print_number_table_attribute(Class_File class_file, Line_Number_Table_Attribute *line_number_table);
void print_source_file_attribute(Class_File class_file, Source_File_Attribute *source_file);
void print_methods_attributes(Class_File class_file, Attribute_Info attribute_info);

void print_fields(Class_File class_file);
void print_methods(Class_File class_file);
void print_attributes(Class_File class_file);

/* INSTRUCTIONS */
void print_newarray(u1 code);
void print_instructions(Class_File class_file, Code_Attribute *code_attribute);

#endif