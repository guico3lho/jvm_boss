#include "attribute_info.hpp"

void read_attribute_info(FILE *file, Class_File *class_file) {
  for (int i = 0; i < class_file->attributes_count ; i++)
    class_file->attributes[i] = get_attribute_info(file, class_file);
}

Attribute_Info read_const_value_attribute(FILE *file, Attribute_Info attribute_info) {
  attribute_info.const_value = (Const_Value_Attribute*) malloc(sizeof(Const_Value_Attribute));
  attribute_info.const_value->const_value_index = read_2_bytes(file);
  return attribute_info;
}

Attribute_Info read_code_attribute(FILE *file, Class_File *class_file, Attribute_Info attribute_info) {
  attribute_info.code = (Code_Attribute*) malloc(sizeof(Code_Attribute));

  attribute_info.code->max_stack = read_2_bytes(file);
  attribute_info.code->max_locals = read_2_bytes(file);

  attribute_info.code->code_length = read_4_bytes(file);
  attribute_info.code->code = (u1*) malloc(sizeof(u1) *attribute_info.code->code_length);

  for (int i = 0; i < (int) attribute_info.code->code_length; i++) 
    attribute_info.code->code[i] = read_1_byte(file);

  attribute_info.code->exception_table_length = read_2_bytes(file);
  attribute_info.code->exception_table = (Code_Exception*) malloc(sizeof(Code_Exception) * attribute_info.code->exception_table_length);

  for (int j = 0; j < attribute_info.code->exception_table_length; j++) {
    attribute_info.code->exception_table[j].start_pc = read_2_bytes(file);
    attribute_info.code->exception_table[j].end_pc = read_2_bytes(file);
    attribute_info.code->exception_table[j].handler_pc = read_2_bytes(file);
    attribute_info.code->exception_table[j].catch_type = read_2_bytes(file);
  }

  attribute_info.code->attributes_count = read_2_bytes(file);
  attribute_info.code->attributes = (Attribute_Info*) malloc(sizeof(Attribute_Info) * attribute_info.code->attributes_count);

  for (int k = 0; k < attribute_info.code->attributes_count; k++)
    attribute_info.code->attributes[k] = get_attribute_info(file, class_file);

  return attribute_info;
}

Attribute_Info read_exception_attribute(FILE *file, Attribute_Info attribute_info) {
  attribute_info.exception = (Exception*) malloc(sizeof(Exception));
  attribute_info.exception->number_exceptions = read_2_bytes(file);

  for (int i = 0; i < attribute_info.exception->number_exceptions; i++)
    attribute_info.exception->exception_index_table[i] = read_2_bytes(file);

  return attribute_info;
}

Attribute_Info read_inner_class_attribute(FILE *file, Attribute_Info attribute_info) {
  attribute_info.inner_class = (Inner_Class_Attribute*) malloc(sizeof(Inner_Class_Attribute));
  attribute_info.inner_class->number_of_classes = read_2_bytes(file);
  attribute_info.inner_class->inner_class_data = (Inner_Class_Attribute*) malloc(attribute_info.inner_class->number_of_classes * sizeof(Inner_Class_Attribute));

  for (int i = 0; i < attribute_info.inner_class->number_of_classes; i++)
    attribute_info.inner_class->inner_class_data[i] = read_inner_class_attributes(file);

  return attribute_info;
}

Inner_Class_Attribute read_inner_class_attributes(FILE *file) {
  Inner_Class_Attribute inner_class;

  inner_class.number_of_classes = read_2_bytes(file);
  inner_class.inner_class_data = (Inner_Class_Attribute*) malloc(inner_class.number_of_classes * sizeof(Inner_Class_Attribute));

  for (int i = 0; i < inner_class.number_of_classes; i++)
    inner_class.inner_class_data[i] = read_inner_class_attributes(file); 

  return inner_class;
}

Attribute_Info read_source_file_attribute(FILE *file, Attribute_Info attribute_info) {
  attribute_info.source_file = (Source_File_Attribute*) malloc(sizeof(Source_File_Attribute));
  attribute_info.source_file->source_file_index = read_2_bytes(file);
  return attribute_info;
}

Attribute_Info read_line_number_table_attribute(FILE *file, Attribute_Info attribute_info) {
  attribute_info.line_number_table = (Line_Number_Table_Attribute*) malloc(sizeof(Line_Number_Table_Attribute));
  attribute_info.line_number_table->line_number_table_length = read_2_bytes(file);
  attribute_info.line_number_table->table = (Line_Number_Table_Data*) malloc(attribute_info.line_number_table->line_number_table_length * sizeof(Line_Number_Table_Data));

  for (int i = 0; i < attribute_info.line_number_table->line_number_table_length; i++)
    attribute_info.line_number_table->table[i] = read_line_number_table_data(file);

  return attribute_info;
}

Line_Number_Table_Data read_line_number_table_data(FILE *file) {
  Line_Number_Table_Data line_number_table_data;

  line_number_table_data.start_pc = read_2_bytes(file);
  line_number_table_data.line_number = read_2_bytes(file);

  return line_number_table_data;
}

void read_local_variable_table_attribute(FILE *file, Attribute_Info *attribute_info) {

  attribute_info->local_variable_table->local_variable_table_length = read_2_bytes(file);

  attribute_info->local_variable_table->table = (Local_Variable_Table_Data*) 
    malloc(attribute_info->local_variable_table->local_variable_table_length * sizeof(Local_Variable_Table_Data));

  for (int i = 0;i < attribute_info->local_variable_table->local_variable_table_length; i++)
    attribute_info->local_variable_table->table[i] = read_local_variable_table_data(file);
}

Local_Variable_Table_Data read_local_variable_table_data(FILE *file) {
    Local_Variable_Table_Data local_variable_table_data;

    local_variable_table_data.start_pc = read_2_bytes(file);
    local_variable_table_data.length = read_2_bytes(file);
    local_variable_table_data.name_index = read_2_bytes(file);
    local_variable_table_data.descriptor_index = read_2_bytes(file);
    local_variable_table_data.index = read_2_bytes(file);

    return local_variable_table_data;
}

Attribute_Info get_attribute_info(FILE *file, Class_File *class_file) {
  Attribute_Info attribute_info;
  attribute_info.attribute_name_index = read_2_bytes(file);
  attribute_info.attribute_length = read_4_bytes(file);

  std::string attribute_name = get_cp_info_utf8(*class_file, attribute_info.attribute_name_index );
  if (DEBUG) std::cout << "Attribute_name: " << attribute_name << std::endl;

  if (attribute_name == "Code") {
    if (DEBUG) std::cout << "Reading Code\n";
    attribute_info = read_code_attribute(file, class_file, attribute_info);
  }
  else if (attribute_name == "ConstantValue") {
    if (DEBUG) std::cout << "Reading constant value\n";
    attribute_info = read_const_value_attribute(file, attribute_info);
  }
  else if (attribute_name == "Exceptions") {
    if (DEBUG) std::cout << "Reading exception\n";
    attribute_info = read_exception_attribute(file, attribute_info);
  }
  else if (attribute_name == "InnerClasses") {
    if (DEBUG) std::cout << "Reading inner classes\n";
    attribute_info = read_inner_class_attribute(file, attribute_info);
  } 
  else if (attribute_name == "Synthetic") {
    if (DEBUG) std::cout << "Reading Synthetic\n"; // Fazer nada?
  }
  else if (attribute_name == "SourceFile") {
    if (DEBUG) std::cout << "Reading Source File\n";
    attribute_info = read_source_file_attribute(file, attribute_info);
  }
  else if (attribute_name == "LineNumberTable") {
    if (DEBUG) std::cout << "Reading Line Number Table\n";
    attribute_info = read_line_number_table_attribute(file, attribute_info);
  }
  else if (attribute_name == "LocalVariableTable") {
    if (DEBUG) std::cout << "Reading Local Variable Table \n";
    read_local_variable_table_attribute(file, &attribute_info);
  }
  else {
    if (DEBUG) std::cout << "Attributo Desconhecido...\n";
    if (DEBUG) std::cout << "Attribute Lenght: " << attribute_info.attribute_length << "\n" ;

    // ignora atributos desconhecidos silenciosamente
    attribute_info.info = (u1*) malloc(attribute_info.attribute_length * sizeof(u1));

    for (int j = 0; (unsigned)j < attribute_info.attribute_length; j++) {
      if (DEBUG) std::cout << "reading byte " << j << std::endl;
      attribute_info.info[j] = read_1_byte(file);
      if (DEBUG) std::cout << "read byte\n";
    }
  }

  return attribute_info;
}