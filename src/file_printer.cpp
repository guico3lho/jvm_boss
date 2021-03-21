#include "file_printer.hpp"

void print_basic_info(std::string filename, Class_File_Format class_file) {
  std::cout << "------------ Basic Info ------------" << std::endl;
  std::cout << "Filename:             " << filename << std::endl;
  printf("Magic Number:         0x%0X\n", class_file.magic_number);
  printf("Minor Version:        %d\n", class_file.minor_version);
  printf("Major version:        %d\n", class_file.major_version);
  printf("Contanst pool count:  %d\n", class_file.constant_pool_count);
  printf("Access flags:         0x%.4x\n", class_file.access_flags);
  printf("This class:           cp_info #%d <", class_file.this_class);

  std::cout << get_cp_info_utf8(class_file.constant_pool,
  class_file.constant_pool[class_file.this_class - 1].class_name - 1)
  << ">";

  printf("\nSuper class:          cp_info #%d <", class_file.super_class);
  std::cout << get_cp_info_utf8(class_file.constant_pool, 
  class_file.constant_pool[class_file.super_class - 1].class_name - 1)
  << ">";

  printf("\nInterface count:      %d\n", class_file.interfaces_count);
  printf("Field count:          %d\n", class_file.fields_count);
  printf("Methods count:        %d\n", class_file.methods_count);
  printf("Attributes count:     %d\n", class_file.attributes_count);
}

void print_cp_info_int(Cp_Info cp_info) {
  // Valor da constante int, em big-endian
  printf("Int\n");
  printf("Int Value: %d\n", cp_info.int_bytes);
}

void print_cp_info_float(Cp_Info cp_info) {
  printf("Float\n");
  float float_value;
  memcpy(&float_value, &(cp_info.float_bytes), sizeof(float));
  // representa o valor da constante float em big-endian, no formato IEEE-754
  printf("Float Value: %lf\n", float_value);
}

void print_cp_info_long(Cp_Info cp_info) {
  printf("Long\n");
  long read_long_value;

  // Constante Int de 8 bytes em big-endian unsigned
  std::cout << "\tHigh:\t0x" << std::hex << cp_info.long_high_bytes << std::endl;
  std::cout << "\tLow:\t0x" << std::hex << cp_info.long_low_bytes << std::endl;

  memcpy(&read_long_value, &(cp_info.long_high_bytes), sizeof(long));
  memcpy(&read_long_value, &(cp_info.long_low_bytes), sizeof(long));
  printf("\tLong Value: %ld\n", read_long_value);
}

void print_cp_info_double(Cp_Info cp_info) {
  double read_double_value;
  u8 aux;

  printf("Double\n");
  std::cout << "\tHigh:\t0x"<< std::hex << cp_info.double_high_bytes << std::endl;
  std::cout << "\tLow:\t0x"<< std::hex << cp_info.double_low_bytes << std::endl;

  // Constante double de 8 bytes em big-endian no formato IEEE-754
  aux = ((u8)cp_info.double_high_bytes << 32) | cp_info.double_low_bytes;
  memcpy(&read_double_value, &aux, sizeof(double));
  std::cout << "\tDouble Value:\t"<< read_double_value << std::endl;
}

void print_cp_info_class(Class_File_Format class_file, Cp_Info cp_info) {
  std::cout << "Class" << "\t\t#" << std::dec << cp_info.class_name;
  std::cout << "\t\t\t" << get_cp_info_utf8(class_file.constant_pool, cp_info.class_name - 1);
}

void print_cp_info_string(Class_File_Format class_file, Cp_Info cp_info) {
  printf("String\t\t#%d\t\t\t", cp_info.string_bytes);
  std::cout << get_cp_info_utf8(class_file.constant_pool, cp_info.string_bytes - 1);
}

void print_cp_info_field(Class_File_Format class_file, Cp_Info cp_info) {
  printf("Fieldref\t\t#%d.#%d\t\t\t", cp_info.field_ref_class_index, cp_info.field_ref_name_type_index);
  std::cout << get_cp_info_utf8(class_file.constant_pool, cp_info.field_ref_class_index - 1);
  std::cout << "." << get_cp_info_utf8(class_file.constant_pool, cp_info.field_ref_name_type_index - 1);
}

void print_cp_info_method(Class_File_Format class_file, Cp_Info cp_info) {
  printf("Methodref\t\t#%d.#%d\t\t\t", cp_info.method_ref_index, cp_info.method_ref_name_and_type);
  std::cout << get_cp_info_utf8(class_file.constant_pool, cp_info.method_ref_index - 1);
  std::cout << "." << get_cp_info_utf8(class_file.constant_pool, cp_info.method_ref_name_and_type - 1);
}

void print_cp_info_interface_method(Class_File_Format class_file, Cp_Info cp_info) {
  std::cout << "CONSTANT_INTERFACE_METHOD_REF" << std::endl;

  // Nome da interface que contem a declaração do metodo
  std::cout << "\tIndex:\t#" << std::endl;
  std::cout << get_cp_info_utf8(class_file.constant_pool, cp_info.interface_method_ref_index - 1) << std::endl;

  // Nome e tipo do método
  std::cout << "Name and Type:"<< std::endl;
  std::cout << get_cp_info_utf8(class_file.constant_pool, cp_info.interface_method_ref_name_type - 1);
}

void print_cp_info_name_type(Class_File_Format class_file, Cp_Info cp_info) {
  printf("NameAndType\t#%d:#%d\t\t\t", cp_info.name_type_index, cp_info.name_type_descriptor_index);
  std::cout << get_cp_info_utf8(class_file.constant_pool, cp_info.name_type_index - 1);
  std::cout << ":" << get_cp_info_utf8(class_file.constant_pool, cp_info.name_type_descriptor_index - 1);
}

void print_constant_pool(Class_File_Format class_file) {
  std::cout << "\n------------ Constant Pool ------------\n";
  Cp_Info current_cp_info;

  for (int i = 0; i < class_file.constant_pool_count - 1; i++) {
    // std::cout << "\n#" << std::dec << i + 1 << std::endl;
    printf("\n#%d = ", i + 1);
    current_cp_info = class_file.constant_pool[i];

    switch (current_cp_info.tag) {
      case CONSTANT_UTF8:
        std::cout << "Utf8\t\t" << current_cp_info.UTF8_bytes;
        // std::cout << "\tLength: " << current_cp_info.UTF8_size;
        break;
      case CONSTANT_INT:
        print_cp_info_int(current_cp_info);
        break;
      case CONSTANT_FLOAT:
        print_cp_info_float(current_cp_info);
        break;
      case CONSTANT_LONG:
        print_cp_info_long(current_cp_info);
        break;
      case CONSTANT_DOUBLE:
        print_cp_info_double(current_cp_info);
        break;
      case CONSTANT_CLASS :
        print_cp_info_class(class_file, current_cp_info);
        break;
      case CONSTANT_STRING:
        print_cp_info_string(class_file, current_cp_info);
        break;
      case CONSTANT_FIELD_REF:
        print_cp_info_field(class_file, current_cp_info);
        break;
      case CONSTANT_METHOD_REF:
        print_cp_info_method(class_file, current_cp_info);
        break;
      case CONSTANT_INTERFACE_METHOD_REF:
        print_cp_info_interface_method(class_file, current_cp_info);
        break;
      case CONSTANT_NAME_TYPE:
        print_cp_info_name_type(class_file, current_cp_info);
        break;
      case CONSTANT_EMPTY:
        std::cout << "\tEmpty Constant"<< std::endl;
        break;
      default:
        printf("Invalid tag number: %d\nEncerrando programa.\n", current_cp_info.tag);
        exit(1);
    }
  }
}

void print_interfaces(Class_File_Format class_file){
  std::cout << std::endl << "------------ Interfaces ------------"<< std::endl;
  std::cout << "Interfaces Count: " << class_file.interfaces_count << std::endl;

  for (int i = 0; i < class_file.interfaces_count; i++) {
    std::cout << "Interfaces"<< std::endl;

    std::cout << "\tInterface #"<< std::dec << class_file.interfaces[i].interface_table;
    std::cout << "\t" << get_cp_info_utf8(class_file.constant_pool, (class_file.interfaces->interface_table + i) - 1) << std::endl;
  }
}

void print_code_attribute(Class_File_Format class_file, Code_Attribute *code_attribute) {
  printf("Code length: %d\n", code_attribute->code_length);
  printf("Exception table length: %d\n", code_attribute->exception_table_length);

  printf("Code: \n");
  printf("  stack=%d, locals=%d \n", code_attribute->max_stack, code_attribute->max_locals);
  // print_instructions(class_file, code_attribute);

  printf("Attributes count: %d\n", code_attribute->attributes_count);
  for (int i = 0; i < code_attribute->attributes_count; ++i) {
    print_methods_attributes(class_file, code_attribute->attributes[i]);
  }
}

void print_constant_value_attribute(Class_File_Format class_file, Const_Value_Attribute *const_value) {
  printf("Constant value index: %d\n", const_value->const_value_index);
}

void print_number_table_attribute(Class_File_Format class_file, Line_Number_Table_Attribute *line_number_table) {
  printf("Line number table length: %d\n", line_number_table->line_number_table_length);

  for (int i = 0; i < line_number_table->line_number_table_length; i++) {
    printf("\tline: %d: %d\n", line_number_table->table[i].line_number, line_number_table->table[i].start_pc);
  }
}

void print_source_file_attribute(Class_File_Format class_file, Source_File_Attribute *source_file) {
  printf("Sourcefile index: #%d\n", source_file->source_file_index);
  std::cout << get_cp_info_utf8(class_file.constant_pool, source_file->source_file_index - 1);
}

void print_methods_attributes(Class_File_Format class_file, Attribute_Info attribute_info) {
  printf("Attribute length: %d\n", attribute_info.attribute_length) ;

  printf("Attribute name index: cp info #%d ", attribute_info.attribute_name_index);
  std::string attribute_type = get_cp_info_utf8(class_file.constant_pool, attribute_info.attribute_name_index - 1);
  std::cout << attribute_type << std::endl;


  if (!attribute_type.compare("Code"))   {
    print_code_attribute(class_file, attribute_info.code);
  }
  else if (attribute_type == "ConstantValue") {
    print_constant_value_attribute(class_file, attribute_info.const_value);
  }
  else if (!attribute_type.compare("LineNumberTable")) {
    print_number_table_attribute(class_file, attribute_info.line_number_table);
  }
  else if (!attribute_type.compare("SourceFile")) {
    print_source_file_attribute(class_file, attribute_info.source_file);
  }
}

void print_fields(Class_File_Format class_file) {
  std::cout << "\n------------ Fields  ------------\n";
  std::cout << "Fields Count: " << class_file.fields_count << std::endl;

  if (class_file.fields_count != 0) {
    for (int i = 0; i < class_file.fields_count; i++) {
      printf("FIELDS_INFO[%d]\n", i);

      printf("\tName:             cp_info_#%d ", class_file.fields[i].name_index);
      std::cout << get_cp_info_utf8(class_file.constant_pool, class_file.fields[i].name_index - 1) << std::endl;

      printf("\tDescriptor:       cp_info_#%d ", class_file.fields[i].descriptor_index);
      std::cout << get_cp_info_utf8(class_file.constant_pool, class_file.fields[i].descriptor_index - 1) << std::endl;

      printf("\tAccess Flag:      0x%04x ", class_file.fields[i].access_flag);
      printf("%d\n", class_file.fields[i].access_flag);

      printf("\tAttributes count: %d        \n\n",class_file.fields[i].atributes_count);

      Field_Info field_info = class_file.fields[i];

      for (int j = 0; j < field_info.atributes_count; j++) {
        print_methods_attributes(class_file, field_info.attributes[j]);
      }
    }
  }
}

void print_methods(Class_File_Format class_file) {
  printf("\n------------ Methods  ------------\n");
  std::cout << "Methods Count: " << class_file.methods_count << std::endl;

  for (int i = 0; i < class_file.methods_count; i++) {
    printf("\n>METHOD INFO[%d]\n\n", i);
    Method_Info *method_info = class_file.methods + i;

    printf("Name Index: #%d ",method_info->name_index);
    std::cout << get_cp_info_utf8(class_file.constant_pool, method_info->name_index - 1) << std::endl;

    printf("Descriptor Index: #%d ",method_info->descriptor_index);
    std::cout << get_cp_info_utf8(class_file.constant_pool, method_info->descriptor_index - 1) << std::endl;

    printf("Access Flag: 0x%04x\n", method_info->access_flags);
    printf("Attributes Count: %d\n",method_info->attributes_count);
    printf("\nMETHOD ATTRIBUTES:\n");

    for (int j = 0; j < method_info->attributes_count; j++) {
      printf("\n------------- Method Attributte[%d] -------------\n", j);
      print_methods_attributes(class_file, method_info->attributes[j]);
    }
  }
}

void print_attributes(Class_File_Format class_file) {
  std::cout << "\n------------- Attributtes Info -------------" << std::endl;
  printf("Attribute length: %d\n", class_file.attributes->attribute_length) ;

  printf("#%d\t", class_file.attributes[0].attribute_name_index);
  std::string attribute_type = get_cp_info_utf8(class_file.constant_pool, class_file.attributes->attribute_name_index - 1);
  std::cout << attribute_type << std::endl;

  if(!attribute_type.compare("Code")) {
    print_code_attribute(class_file, class_file.attributes->code);
  }
  else if(attribute_type == "ConstantValue"){
    print_constant_value_attribute(class_file, class_file.attributes->const_value);
  }
  else if (!attribute_type.compare("LineNumberTable"))   {
    print_number_table_attribute(class_file, class_file.attributes->line_number_table);
  }
  else if (!attribute_type.compare("SourceFile")) {
    printf("#%d\t", class_file.attributes->source_file->source_file_index);
    std::cout << get_cp_info_utf8(class_file.constant_pool, class_file.attributes->source_file->source_file_index - 1);
  }
}