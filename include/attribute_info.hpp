#ifndef __ATTRIBUTE_INFO_H__
#define __ATTRIBUTE_INFO_H__

#include "file_reader.hpp"

struct Attribute_Info;
struct Class_File_Format;

typedef struct {
  u2 attribute_name_index;
  u4 attribute_length;
  u2 const_value_index;
} Const_Value_Attribute;

typedef struct {
  u2 start_pc;
  u2 end_pc;
  u2 handler_pc;
  u2 catch_type;
} Code_Exception;

typedef struct Code_Attribute{
  u2 max_stack;
  u2 max_locals;
  u4 code_length;
  u1* code;

  u2 exception_table_length;
  Code_Exception* exception_table;

  u2 attributes_count;
  Attribute_Info* attributes;
} Code_Attribute;

typedef struct Attribute_Info{

  u2 attribute_name_index; // valid unsigned 16-bit index into the constant pool of the class
  u4 attribute_length;

  Const_Value_Attribute *const_value;
  Code_Attribute *code;
  u1* info;

} Attribute_Info;

/* ATTRIBUTE_INFO */
Attribute_Info get_attribute_info(FILE *file, Class_File_Format *class_file, Attribute_Info attribute_info);
void read_const_value_attribute(FILE *file, Class_File_Format *class_file, Attribute_Info *attribute_info);
void read_code_attribute(FILE *file, Class_File_Format *class_file, Attribute_Info *attribute_info);

#endif
