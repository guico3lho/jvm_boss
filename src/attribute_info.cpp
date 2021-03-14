#include "attribute_info.hpp"

void read_const_value_attribute(FILE *file, Class_File_Format *class_file, Attribute_Info *attribute_info) {
  attribute_info->const_value->const_value_index = read_2_bytes(file);
}

void read_code_attribute(FILE *file, Class_File_Format *class_file, Attribute_Info *attribute_info) {

  // Attribute_Info *code_attribute_info;
  attribute_info->code->max_stack = read_2_bytes(file);
  attribute_info->code->max_locals = read_2_bytes(file);
  attribute_info->code->code_length = read_4_bytes(file);

  attribute_info->code->code = (u1*) malloc(sizeof(u1) *attribute_info->code->code_length);

  for (int i = 0; (unsigned)i < attribute_info->code->code_length; i++) {
    attribute_info->code->code[i] = read_1_byte(file);
  }

  attribute_info->code->exception_table_length = read_2_bytes(file);
  attribute_info->code->exception_table = (Code_Exception*) malloc(sizeof(Code_Exception) * attribute_info->code->exception_table_length);

  for (int j = 0; j < attribute_info->code->exception_table_length; j++) {
    attribute_info->code->exception_table[j].start_pc = read_2_bytes(file);
    attribute_info->code->exception_table[j].end_pc = read_2_bytes(file);
    attribute_info->code->exception_table[j].handler_pc = read_2_bytes(file);
    attribute_info->code->exception_table[j].catch_type = read_2_bytes(file);
  }

  attribute_info->code->attributes_count = read_2_bytes(file);
  attribute_info->code->attributes = (Attribute_Info*) malloc(sizeof(Attribute_Info) * attribute_info->code->attributes_count);

  for (int k = 0; k < attribute_info->code->attributes_count; k++)
    attribute_info->code->attributes[k] = get_attribute_info(file, class_file,  attribute_info->code->attributes[k]);
}

void read_exception_attribute(FILE *file, Attribute_Info *attribute_info) {
  attribute_info->exception->number_exceptions = read_2_bytes(file);

  for (int i = 0; i < attribute_info->exception->number_exceptions; i++)
    attribute_info->exception->exception_index_table[i] = read_2_bytes(file);
}

void read_inner_class_attribute(FILE *file, Attribute_Info *attribute_info) {
  attribute_info->inner_class->number_of_classes = read_2_bytes(file);
  attribute_info->inner_class->inner_class_data = (Inner_Class_Attribute*) malloc(attribute_info->inner_class->number_of_classes * sizeof(Inner_Class_Attribute));

  for (int i = 0; i < attribute_info->inner_class->number_of_classes; i++)
    attribute_info->inner_class->inner_class_data[i] = read_inner_class_attributes(file);
}

Inner_Class_Attribute read_inner_class_attributes(FILE *file) {
  Inner_Class_Attribute inner_class;

  inner_class.number_of_classes = read_2_bytes(file);
  inner_class.inner_class_data = (Inner_Class_Attribute*) malloc(inner_class.number_of_classes * sizeof(Inner_Class_Attribute));

  for (int i = 0; i < inner_class.number_of_classes; i++)
    inner_class.inner_class_data[i] = read_inner_class_attributes(file); 

  return inner_class;
}

void read_source_file_attribute(FILE *file, Attribute_Info *attribute_info) {
  attribute_info->source_file->source_file_index = read_2_bytes(file);
}

void read_line_number_table_attribute(FILE *file, Attribute_Info *attribute_info) {

  attribute_info->line_number_table->line_number_table_length = read_2_bytes(file);
  attribute_info->line_number_table->table = (Line_Number_Table_Data*) malloc(attribute_info->line_number_table->line_number_table_length * sizeof(Line_Number_Table_Data));

  for (int i = 0; i < attribute_info->line_number_table->line_number_table_length; i++)
    attribute_info->line_number_table->table[i] = read_line_number_table_data(file);
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

Attribute_Info get_attribute_info(FILE *file, Class_File_Format *class_file, Attribute_Info attribute_info) {
  if (PRINT) std::cout << "reading basic attribute info\n";
  attribute_info.attribute_name_index = read_2_bytes(file);
  attribute_info.attribute_length = read_4_bytes(file);

  std::string attribute_name =get_cp_info_utf8(class_file->constant_pool, attribute_info.attribute_name_index - 1);
  if (PRINT) std::cout << "Basic info\n";
  if (PRINT) std::cout << "Attribute_name: " << attribute_name << std::endl;

  if (attribute_name == "Code") {
    if (PRINT) std::cout << "Reading code\n";
    read_code_attribute(file, class_file ,&attribute_info);
    return attribute_info;
  }
  else if (attribute_name == "ConstantValue") {
    if (PRINT) std::cout << "Reading constant value\n";
    read_const_value_attribute(file, class_file ,&attribute_info);
  }
  else if (attribute_name == "Exceptions") {
    if (PRINT) std::cout << "exception\n";
    read_exception_attribute(file, &attribute_info);
  }
  else if (attribute_name =="InnerClasses") {
    if (PRINT) std::cout << "Reading inner classes\n";
    read_inner_class_attribute(file, &attribute_info);
  } 
  else if (attribute_name == "Synthetic") {
    if (PRINT) std::cout << "Reading Synthetic\n"; // Fazer nada?
  }
  else if (attribute_name =="SourceFile") {
    if (PRINT) std::cout << "Reading source file\n";
    read_source_file_attribute(file, &attribute_info);
  }
  else if (attribute_name == "LineNumberTable") {
    if (PRINT) std::cout << "Line Number table\n";
    read_line_number_table_attribute(file, &attribute_info);
  }
  else if (attribute_name == "LocalVariableTable") {
    if (PRINT) std::cout << "LocalVariableTable \n";
    read_local_variable_table_attribute(file, &attribute_info);
  }
  else {
    if (PRINT) std::cout << "Attributo Desconhecido...\n";
    if (PRINT) std::cout << "Attribute Lenght: " << attribute_info.attribute_length << "\n" ;

    // ignora atributos irreconhecidos silenciosamente
    attribute_info.info = (u1*) malloc(attribute_info.attribute_length * sizeof(u1));

    for (int j = 0; (unsigned)j < attribute_info.attribute_length; j++) {
      if (PRINT) std::cout << "reading byte " << j << std::endl;
      attribute_info.info[j] = read_1_byte(file);
      if (PRINT) std::cout << "read byte\n";
    }
  }

  return attribute_info;
}