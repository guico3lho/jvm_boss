#ifndef __FILE_READER_H__
#define __FILE_READER_H__

#include "read_bytes.hpp"
#include "cp_info.hpp"
#include "interface_info.hpp"

typedef struct {
  u4 magic_number;

  u2 minor_version;   
  u2 major_version;

  u2 constant_pool_count;   
  Cp_Info *constant_pool;

  u2 access_flags;

  u2 this_class;
  u2 super_class;

  u2 interfaces_count;   
  Interface_Info *interfaces;

  u2 fields_count;   
  // field_info fields[fields_count];

  u2 methods_count;
  // method_info methods[methods_count];

  u2 attributes_count;   
  // attribute_info attributes[attributes_count];
} Class_File_Format;

Class_File_Format read_class_file(std::string filename);
void read_cp_info(FILE *file, Class_File_Format *class_file);

void read_interface_info(FILE *file, Class_File_Format *class_file);
Interface_Info get_interface_info(FILE *file, Class_File_Format *class_file, Interface_Info interface_info);

#endif 
