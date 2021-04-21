/**
 * @file file_printer.cpp
 * @brief Arquivo com funções que imprimem informações para o usuário
*/

#include "file_printer.hpp"

void print_major_version(u2 major_version) {

  switch(major_version) {
    case 52:
      printf("Java SE 8");
      break;
    case 51:
      printf("Java SE 7");
      break;
    case 50:
      printf("Java SE 6.0");
      break;
    case 49:
      printf("Java SE 5.0");
      break;
    case 48:
      printf("JDK 1.4");
      break;
    case 47:
      printf("JDK 1.3");
      break;
    case 46:
      printf("JDK 1.2");
      break;
    case 45:
      printf("JDK 1.1");
      break;
  }
  printf("\n");
}

void check_flag(u2 access_flags, int constant_access_flag, std::string flag_name) {
  if(access_flags & constant_access_flag) {
    std::cout << flag_name << " ";
  }
}

void print_access_flags(u2 access_flags) {
  printf("0x%.4x: ", access_flags);

  std::string flags[15] = {
    "ACC_PUBLIC", "ACC_SUPER", "ACC_PROTECTED", "ACC_STATIC", "ACC_FINAL",
    "ACC_VOLATILE", "ACC_TRANSIENT", "ACC_SYNTHETIC", "ACC_ENUM", "ACC_SUPER", "ACC_INTERFACE"
    "ACC_ABSTRACT", "ACC_ANNOTATION", "ACC_NATIVE", "ACC_STRICT"
  };

  check_flag(access_flags, ACC_PUBLIC, flags[0]);
  check_flag(access_flags, ACC_PRIVATE, flags[1]);
  check_flag(access_flags, ACC_PROTECTED, flags[2]);
  check_flag(access_flags, ACC_STATIC, flags[3]);
  check_flag(access_flags, ACC_FINAL, flags[4]);
  check_flag(access_flags, ACC_VOLATILE, flags[5]);
  check_flag(access_flags, ACC_TRANSIENT, flags[6]);
  check_flag(access_flags, ACC_SYNTHETIC, flags[7]);
  check_flag(access_flags, ACC_ENUM, flags[8]);
  check_flag(access_flags, ACC_SUPER, flags[9]);
  check_flag(access_flags, ACC_INTERFACE, flags[10]);
  check_flag(access_flags, ACC_ABSTRACT, flags[11]);
  check_flag(access_flags, ACC_ANNOTATION, flags[12]);
  check_flag(access_flags, ACC_NATIVE, flags[13]);
  check_flag(access_flags, ACC_STRICT, flags[14]);

  printf("\n");
}

void print_basic_info(std::string filename, Class_File class_file) {
  std::cout << "------------ Basic Info ------------" << std::endl;
  std::cout << "File:             " << filename << std::endl;
  printf("Magic Number:         0x%0X\n", class_file.magic_number);
  printf("Minor Version:        %d\n", class_file.minor_version);
  printf("Major version:        %d: ", class_file.major_version);
  print_major_version(class_file.major_version);
  printf("Contanst pool count:  %d\n", class_file.constant_pool_count);
  printf("Access flags:         ");
  print_access_flags(class_file.access_flags);
  printf("This class:           #%d <", class_file.this_class);

  std::cout << get_cp_info_utf8(class_file,class_file.constant_pool[class_file.this_class].Class.class_name)
  << ">";

  printf("\nSuper class:          #%d <", class_file.super_class);
  std::cout << get_cp_info_utf8(class_file, class_file.constant_pool[class_file.super_class].Class.class_name)
  << ">";

  printf("\nInterface count:      %d\n", class_file.interfaces_count);
  printf("Field count:          %d\n", class_file.fields_count);
  printf("Methods count:        %d\n", class_file.methods_count);
  printf("Attributes count:     %d\n", class_file.attributes_count);
}

/* CONSTANT POOL */

void print_cp_info_int(Cp_Info cp_info) {
  printf("Integer\t\t%d\t\tHex: 0x%x",  cp_info.Integer.bytes, cp_info.Integer.bytes);
}

void print_cp_info_float(Cp_Info cp_info) {
  float float_value;
  memcpy(&float_value, &(cp_info.Float.bytes), sizeof(float));
  printf("Float\t\t%f", float_value);
}

void print_cp_info_long(Cp_Info cp_info) {
  u8 aux;
  long long_value;

  aux = ((u8) cp_info.Long.high_bytes << 32) | cp_info.Long.low_bytes;
  memcpy(&long_value, &aux, sizeof(long));

  printf("Long\t\t%ld\t\t", long_value);
  printf("High: 0x%x | Low: 0x%x", cp_info.Long.high_bytes, cp_info.Long.low_bytes);
}

void print_cp_info_double(Cp_Info cp_info) {
  double read_double_value;
  u8 aux;

  printf("Double\n");
  std::cout << "\tHigh:\t0x"<< std::hex << cp_info.Double.high_bytes << std::endl;
  std::cout << "\tLow:\t0x"<< std::hex << cp_info.Double.low_bytes << std::endl;

  // Constante double de 8 bytes em big-endian no formato IEEE-754
  aux = ((u8)cp_info.Double.high_bytes << 32) | cp_info.Double.low_bytes;
  memcpy(&read_double_value, &aux, sizeof(double));
  std::cout << "\tDouble Value:\t"<< read_double_value << std::endl;
}

void print_cp_info_class(Class_File class_file, Cp_Info cp_info) {
  std::cout << "Class" << "\t\t#" << std::dec << cp_info.Class.class_name;
  std::cout << "\t\t\t" << get_cp_info_utf8(class_file, cp_info.Class.class_name);
}

void print_cp_info_string(Class_File class_file, Cp_Info cp_info) {
  printf("String\t\t#%d\t\t\t", cp_info.String.string_index);
  std::cout << get_cp_info_utf8(class_file, cp_info.String.string_index);
}

void print_cp_info_field(Class_File class_file, Cp_Info cp_info) {
  printf("Fieldref\t\t#%d.#%d\t\t\t", cp_info.Fieldref.class_index, cp_info.Fieldref.name_and_type_index);
  std::cout << get_cp_info_utf8(class_file, cp_info.Fieldref.class_index);
  std::cout << "." << get_cp_info_utf8(class_file, cp_info.Fieldref.name_and_type_index);
}

void print_cp_info_method(Class_File class_file, Cp_Info cp_info) {
  printf("Methodref\t\t#%d.#%d\t\t\t", cp_info.Methodref.class_index, cp_info.Methodref.name_and_type_index);
  std::cout << get_cp_info_utf8(class_file, cp_info.Methodref.class_index);
  std::cout << "." << get_cp_info_utf8(class_file, cp_info.Methodref.name_and_type_index);
}

void print_cp_info_interface_method(Class_File class_file, Cp_Info cp_info) {
  std::cout << "CONSTANT_INTERFACE_METHOD_REF" << std::endl;

  // Nome da interface que contem a declaração do metodo
  std::cout << "\tIndex:\t#" << std::endl;
  std::cout << get_cp_info_utf8(class_file, cp_info.InterfaceMethodref.class_index) << std::endl;

  // Nome e tipo do método
  std::cout << "Name and Type:"<< std::endl;
  std::cout << get_cp_info_utf8(class_file, cp_info.InterfaceMethodref.name_and_type_index);
}

void print_cp_info_name_type(Class_File class_file, Cp_Info cp_info) {
  printf("NameAndType\t#%d:#%d\t\t\t", cp_info.NameAndType.name_index, cp_info.NameAndType.descriptor_index);
  std::cout << get_cp_info_utf8(class_file, cp_info.NameAndType.name_index);
  std::cout << ":" << get_cp_info_utf8(class_file, cp_info.NameAndType.descriptor_index);
}

void print_constant_pool(Class_File class_file) {
  std::cout << "\n------------ Constant Pool ------------\n";
  Cp_Info current_cp_info;

  for (int i = 1; i < class_file.constant_pool_count; i++) {
    printf("\n#%d = ", i);
    current_cp_info = class_file.constant_pool[i];

    switch (current_cp_info.tag) {
      case CONSTANT_UTF8:
        std::cout << "Utf8\t\t" << current_cp_info.Utf8.bytes;
        // std::cout << "\tLength: " << current_cp_info.Utf8.length;
        break;
      case CONSTANT_INT:
        print_cp_info_int(current_cp_info);
        break;
      case CONSTANT_FLOAT:
        print_cp_info_float(current_cp_info);
        break;
      case CONSTANT_LONG:
        print_cp_info_long(current_cp_info);
        i++;
        break;
      case CONSTANT_DOUBLE:
        print_cp_info_double(current_cp_info);
        i++;
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

/* INTERFACES */

void print_interfaces(Class_File class_file){
  std::cout << std::endl << "------------ Interfaces ------------"<< std::endl;
  std::cout << "Interfaces Count: " << class_file.interfaces_count << std::endl;

  for (int i = 0; i < class_file.interfaces_count; i++) {
    std::cout << "Interfaces"<< std::endl;

    std::cout << "\tInterface #"<< std::dec << class_file.interfaces[i].interface_table;
    std::cout << "\t" << get_cp_info_utf8(class_file, (class_file.interfaces->interface_table + i)) << std::endl;
  }
}

/* ATTRIBUTES */

void print_code_attribute(Class_File class_file, Code_Attribute *code_attribute) {
  printf("Code length: %d\n", code_attribute->code_length);
  printf("Code Attributes count: %d\n", code_attribute->attributes_count);
  printf("Exception table length: %d\n", code_attribute->exception_table_length);

  printf("Code: \n");
  printf("  stack=%d, locals=%d \n", code_attribute->max_stack, code_attribute->max_locals);
  print_instructions(class_file, code_attribute);

  for (int i = 0; i < code_attribute->attributes_count; ++i) {
    printf("\n##### Code Attribute[%d] info ######\n", i);
    print_methods_attributes(class_file, code_attribute->attributes[i]);
  }
}

void print_constant_value_attribute(Class_File class_file, Const_Value_Attribute *const_value) {
  printf("Constant value index: %d\n", const_value->const_value_index);
}

void print_number_table_attribute(Class_File class_file, Line_Number_Table_Attribute *line_number_table) {
  printf("Line number table - length: %d\n\n", line_number_table->line_number_table_length);

  for (int i = 0; i < line_number_table->line_number_table_length; i++) {
    printf("line %d: %d\n", line_number_table->table[i].line_number, line_number_table->table[i].start_pc);
  }
}

void print_source_file_attribute(Class_File class_file, Source_File_Attribute *source_file) {
  printf("#%d\t", source_file->source_file_index);
  std::cout << get_cp_info_utf8(class_file, source_file->source_file_index);
}

void print_methods_attributes(Class_File class_file, Attribute_Info attribute_info) {
  std::string attribute_type = get_cp_info_utf8(class_file, attribute_info.attribute_name_index);
  std::cout << "Attribute Name: " << attribute_type << std::endl;
  printf("Attribute Index: #%d\n", attribute_info.attribute_name_index);
  printf("Attribute length: %d\n", attribute_info.attribute_length) ;

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

void print_fields(Class_File class_file) {
  std::cout << "\n------------ Fields  ------------\n";
  std::cout << "Fields Count: " << class_file.fields_count << std::endl;

  if (class_file.fields_count != 0) {
    for (int i = 0; i < class_file.fields_count; i++) {
      printf("FIELDS_INFO[%d]\n", i);

      printf("\tName:             cp_info_#%d ", class_file.fields[i].name_index);
      std::cout << get_cp_info_utf8(class_file, class_file.fields[i].name_index) << std::endl;

      printf("\tDescriptor:       cp_info_#%d ", class_file.fields[i].descriptor_index);
      std::cout << get_cp_info_utf8(class_file, class_file.fields[i].descriptor_index) << std::endl;

      printf("\tAccess Flag:      0x%04x ", class_file.fields[i].access_flags);
      printf("%d\n", class_file.fields[i].access_flags);

      printf("\tAttributes count: %d        \n\n",class_file.fields[i].atributes_count);

      Field_Info field_info = class_file.fields[i];

      for (int j = 0; j < field_info.atributes_count; j++) {
        print_methods_attributes(class_file, field_info.attributes[j]);
      }
    }
  }
}

void print_methods(Class_File class_file) {
  printf("\n------------ Methods  ------------\n");
  std::cout << "Methods Count: " << class_file.methods_count << std::endl;

  for (int i = 0; i < class_file.methods_count; i++) {
    printf("\n========== METHOD INFO[%d] ==========\n\n", i);
    Method_Info *method_info = class_file.methods + i;

    printf("Name Index: #%d ",method_info->name_index);
    std::cout << get_cp_info_utf8(class_file, method_info->name_index) << std::endl;

    printf("Descriptor Index: #%d ", method_info->descriptor_index);
    std::cout << get_cp_info_utf8(class_file, method_info->descriptor_index) << std::endl;

    printf("Access flags: ");
    print_access_flags(method_info->access_flags);

    printf("Attributes Count: %d\n",method_info->attributes_count);
    printf("\nMETHOD ATTRIBUTES:\n");

    for (int j = 0; j < method_info->attributes_count; j++) {
      printf("\n------------- Method Attributte[%d] -------------\n", j);
      print_methods_attributes(class_file, method_info->attributes[j]);
    }
  }
}

void print_attributes(Class_File class_file) {
  std::cout << "\n------------- Attributtes Info -------------" << std::endl;
  printf("Attribute length: %d\n", class_file.attributes->attribute_length) ;

  printf("#%d\t", class_file.attributes[0].attribute_name_index);
  std::string attribute_type = get_cp_info_utf8(class_file, class_file.attributes->attribute_name_index);
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
    print_source_file_attribute(class_file, class_file.attributes->source_file);
  }
}

void print_newarray(u1 code) {
  printf(" 0x%x = %d", code, code);
  switch (code) {
    case T_BOOLEAN: 
      std::cout << " (bool)"; 
      break;
    case T_CHAR: 
      std::cout << " (char)"; 
      break;
    case T_FLOAT: 
      std::cout << " (float)"; 
      break;
    case T_DOUBLE: 
      std::cout << " (double)"; 
      break;
    case T_BYTE: 
      std::cout << " (byte)"; 
      break;
    case T_SHORT: 
      std::cout << " (short)"; 
      break;
    case T_INT: 
      std::cout << " (int)"; 
      break;
    case T_LONG: 
      std::cout << " (long)"; 
      break;
  }
}

void print_instructions(Class_File class_file, Code_Attribute *code_attribute) {
  std::vector<Instruction> instructions = set_instructions();
  std::string str;

  for (int i = 0; i < (int) code_attribute->code_length; i++) {
    int op_code = (int) code_attribute->code[i];
    std::cout << i << ": " << instructions[op_code].name;

    for (int j = 0; j < (int) instructions[op_code].bytes; j++) {
        ++i;
        switch(op_code) {
          case CONSTANT_ldc:
            {
              u1 index = code_attribute->code[i];
              u2 index_utf8 = 0x00 | index;
              std::cout << "\t#" << (int)index << " " << get_cp_info_utf8(class_file, index_utf8);
              j++;
            }
            break;
          case CONSTANT_newarray:
            print_newarray(code_attribute->code[j]);
            j++;
            break;
          case CONSTANT_multianewarray:
            {
              u1 byte1 = code_attribute->code[i];
              u1 byte2 = code_attribute->code[i+1];
              u1 dim = code_attribute->code[i + 2];
              u2 index = (byte1 << 8) | byte2;
              str = get_cp_info_utf8(class_file, index);

              if (!str.empty()) {
                std::cout << "\t#" << std::dec << index << " " << str;
                std::cout << " dim " << (int) dim;
              }
              j++;
            }
            break;
          case CONSTANT_anewarray:
          case CONSTANT_checkcast: 
          case CONSTANT_getfield: 
          case CONSTANT_getstatic:
          case CONSTANT_instanceof: 
          case CONSTANT_invokespecial: 
          case CONSTANT_invokestatic:
          case CONSTANT_invokevirtual:
          case CONSTANT_ldc_w: 
          case CONSTANT_ldc2_w: 
          case CONSTANT_putfield:
          case CONSTANT_putstatic:
            {
              u1 byte1 = code_attribute->code[i];
              u1 byte2 = code_attribute->code[i + 1];
              u2 index = (byte1 << 8) | byte2;
              std::cout << "\t#" << std::dec << index << " " << get_cp_info_utf8(class_file, index);
              i++;
              j++;
            }
            break;
          case CONSTANT_GOTO: 
          case CONSTANT_if_acmpeq:  
          case CONSTANT_if_acmpne:  
          case CONSTANT_if_icmpeq: 
          case CONSTANT_if_icmpne: 
          case CONSTANT_if_icmplt: 
          case CONSTANT_if_icmpge: 
          case CONSTANT_if_icmpgt: 
          case CONSTANT_if_icmple: 
          case CONSTANT_iifeq: 
          case CONSTANT_ifne:
          case CONSTANT_iflt: 
          case CONSTANT_ifge: 
          case CONSTANT_ifgt: 
          case CONSTANT_ifle: 
          case CONSTANT_ifnonull: 
          case CONSTANT_ifnull: 
          case CONSTANT_jsr:
            {
              u1 branchbyte1 = code_attribute->code[i];
              u1 branchbyte2 = code_attribute->code[i + 1];
              u2 address = (branchbyte1 << 8) | branchbyte2;
              printf("\t%d", address);
              i++;
              j++;
            }
            break;
          default:
            printf(" 0x%x", code_attribute->code[j]);
            break;
        }
    }
    printf("\n");
  }
  printf("\n");
}