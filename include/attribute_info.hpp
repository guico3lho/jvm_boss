#ifndef __ATTRIBUTE_INFO_H__
#define __ATTRIBUTE_INFO_H__

#include "file_reader.hpp"

struct Attribute_Info;
struct Class_File;

typedef struct Const_Value_Attribute{
  u2 attribute_name_index;
  u4 attribute_length;
  u2 const_value_index;
} Const_Value_Attribute;

typedef struct Code_Exception{
  u2 start_pc;
  u2 end_pc;
  u2 handler_pc;
  u2 catch_type;
} Code_Exception;

typedef struct Code_Attribute {
  u2 max_stack;
  u2 max_locals;
  u4 code_length;
  u1* code;

  u2 exception_table_length;
  Code_Exception* exception_table;

  u2 attributes_count;
  Attribute_Info* attributes;
} Code_Attribute;

typedef struct Exception{
  u2 number_exceptions;
  u2 *exception_index_table;
} Exception;

typedef struct Inner_Class_Attribute {
  u2 attribute_name_index;
  u4 attribute_length;

  u2 number_of_classes;
  Inner_Class_Attribute *inner_class_data = nullptr;
} Inner_Class_Attribute;

typedef struct Source_File_Attribute {
  u2 source_file_index;
} Source_File_Attribute;

typedef struct Line_Number_Table_Data {
  u2 start_pc;
  u2 line_number;
} Line_Number_Table_Data;

typedef struct Line_Number_Table_Attribute {
  u2 line_number_table_length;
  Line_Number_Table_Data *table;
} Line_Number_Table_Attribute;

typedef struct Local_Variable_Table_Data {
  u2 start_pc;
  u2 length;
  u2 name_index;
  u2 descriptor_index;
  u2 index;
} Local_Variable_Table_Data;

typedef struct Local_Variable_Table_Attribute {
  u2 local_variable_table_length;
  Local_Variable_Table_Data *table;
} Local_Variable_Table_Attribute;

typedef struct Attribute_Info{
  u2 attribute_name_index;
  u4 attribute_length;

  Const_Value_Attribute *const_value = nullptr;
  Code_Attribute *code = nullptr;
  Exception *exception = nullptr;
  Inner_Class_Attribute *inner_class = nullptr;
  Source_File_Attribute *source_file = nullptr;
  Line_Number_Table_Attribute *line_number_table = nullptr;
  Local_Variable_Table_Attribute *local_variable_table = nullptr;
  u1 *info = nullptr;
} Attribute_Info;

void read_attribute_info(FILE *file, Class_File *class_file);
Attribute_Info get_attribute_info(FILE *file, Class_File *class_file);

Attribute_Info read_const_value_attribute(FILE *file, Attribute_Info attribute_info);
Attribute_Info read_code_attribute(FILE *file, Attribute_Info attribute_info);
Attribute_Info read_exception_attribute(FILE *file, Attribute_Info attribute_info);
Attribute_Info read_source_file_attribute(FILE *file, Attribute_Info attribute_info);

Attribute_Info read_inner_class_attribute(FILE *file, Attribute_Info attribute_info);
Inner_Class_Attribute read_inner_class_attributes(FILE *file);

Attribute_Info read_line_number_table_attribute(FILE *file, Attribute_Info attribute_info);
Line_Number_Table_Data read_line_number_table_data(FILE *file);

void read_local_variable_table_attribute(FILE *file, Attribute_Info *attribute_info);
Local_Variable_Table_Data read_local_variable_table_data(FILE *file);

#endif
