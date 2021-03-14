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

  for (int k = 0; k < attribute_info->code->attributes_count; k++){
    attribute_info->code->attributes[k] = get_attribute_info(file, class_file,  attribute_info->code->attributes[k]);
  }
}

void read_exception_attribute(FILE *file, Attribute_Info *attribute_info) {
  attribute_info->exception->number_exceptions = read_2_bytes(file);

  for (int i = 0; i < attribute_info->exception->number_exceptions; i++)
    attribute_info->exception->exception_index_table[i] = read_2_bytes(file);
}

void read_inner_class_attribute(FILE *file, Attribute_Info *attribute_info) {
  attribute_info->inner_class->number_of_classes = read_2_bytes(file);
  attribute_info->inner_class->inner_class_data = (Inner_Class_Attribute*) malloc(attribute_info->inner_class->number_of_classes * sizeof(Inner_Class_Attribute));

  for (int i = 0; i < attribute_info->inner_class->number_of_classes; i++){
    attribute_info->inner_class->inner_class_data[i] = read_inner_class_attributes(file, attribute_info);
  }
}

Inner_Class_Attribute read_inner_class_attributes(FILE *file, Attribute_Info *attribute_info) {
  Inner_Class_Attribute inner_class;

  inner_class.number_of_classes = read_2_bytes(file);
  inner_class.inner_class_data = (Inner_Class_Attribute*) malloc(inner_class.number_of_classes * sizeof(Inner_Class_Attribute));

  for (int i = 0; i < inner_class.number_of_classes; i++){
    inner_class.inner_class_data[i] = read_inner_class_attributes(file, attribute_info); 
  }

  return inner_class;
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
    if (PRINT) std::cout << "Reading Synthetic\n";
    // fazer nada -> eh pra implementar
  }
  // else if (attribute_name =="SourceFile") {
  //   if (PRINT) std::cout << "Reading source file\n";
  //   attribute_info.source_file = source_info->read(file, attribute_info);
  // }
  // else if (attribute_name == "LineNumberTable") {
  //   if (PRINT) std::cout << "line number table\n";
  //   attribute_info.line_number_table = line_number_info->read(file, attribute_info);
  // }
  // else if (attribute_name == "LocalVariableTable") {
  //   if (PRINT) std::cout << "LocalVariableTable \n";
  //   attribute_info.local_variable_table = local_info->read(file, attribute_info);
  // }
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