#include "file_printer.hpp"

void print_basic_info(std::string filename, Class_File class_file) {
  std::cout << "------------ Basic Info ------------" << std::endl;
  std::cout << "Filename:             " << filename << std::endl;
  printf("Magic Number:         0x%0X\n", class_file.magic_number);
  printf("Minor Version:        %d\n", class_file.minor_version);
  printf("Major version:        %d\n", class_file.major_version);
  printf("Contanst pool count:  %d\n", class_file.constant_pool_count);
  printf("Access flags:         0x%.4x\n", class_file.access_flags);
  printf("This class:           #%d <", class_file.this_class);

  std::cout << get_utf8(class_file,
  class_file.constant_pool[class_file.this_class].Class_Info.class_name)
  << ">";

  printf("\nSuper class:          #%d <", class_file.super_class);
  std::cout << get_utf8(class_file, 
  class_file.constant_pool[class_file.super_class].Class_Info.class_name)
  << ">";

  printf("\nInterface count:      %d\n", class_file.interfaces_count);
  printf("Field count:          %d\n", class_file.fields_count);
  printf("Methods count:        %d\n", class_file.methods_count);
  printf("Attributes count:     %d\n", class_file.attributes_count);
}

/* INTERFACES */

void print_interfaces(Class_File class_file){
  std::cout << std::endl << "------------ Interfaces ------------"<< std::endl;
  std::cout << "Interfaces Count: " << class_file.interfaces_count << std::endl;

  for (int i = 0; i < class_file.interfaces_count; i++) {
    std::cout << "Interfaces"<< std::endl;

    std::cout << "\tInterface #"<< std::dec << class_file.interfaces[i].interface_table;
    std::cout << "\t" << get_utf8(class_file, (class_file.interfaces->interface_table + i)) << std::endl;
  }
}

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

/* ATTRIBUTES */

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
  std::cout << get_utf8(class_file, source_file->source_file_index);
}

void print_methods_attributes(Class_File class_file, Attribute_Info attribute_info) {
  std::string attribute_type = get_utf8(class_file, attribute_info.attribute_name_index);
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
      std::cout << get_utf8(class_file, class_file.fields[i].name_index) << std::endl;

      printf("\tDescriptor:       cp_info_#%d ", class_file.fields[i].descriptor_index);
      std::cout << get_utf8(class_file, class_file.fields[i].descriptor_index) << std::endl;

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

void print_methods(Class_File class_file) {
  printf("\n------------ Methods  ------------\n");
  std::cout << "Methods Count: " << class_file.methods_count << std::endl;

  for (int i = 0; i < class_file.methods_count; i++) {
    printf("\n========== METHOD INFO[%d] ==========\n\n", i);
    Method_Info *method_info = class_file.methods + i;

    printf("Name Index: #%d ",method_info->name_index);
    std::cout << get_utf8(class_file, method_info->name_index) << std::endl;

    printf("Descriptor Index: #%d ",method_info->descriptor_index);
    std::cout << get_utf8(class_file, method_info->descriptor_index) << std::endl;

    printf("Access Flag: 0x%04x\n", method_info->access_flags);
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
  std::string attribute_type = get_utf8(class_file, class_file.attributes->attribute_name_index);
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
  Instruction *instructions = set_instructions();

  std::string str;

  for (int i = 0; i < (int) code_attribute->code_length; i++) {

    int op_code = (int) code_attribute->code[i];
    std::cout << i << ": " << instructions[op_code].name;

    for (int j = 0; j < (int) instructions[op_code].bytes; j++) {
        ++i;
        switch(op_code) {
          case ldc:
            {
              u1 index = code_attribute->code[i];
              u2 index_utf8 = 0x00 | index;
              std::cout << " #" << (int)index << " " << get_utf8(class_file, index_utf8);
              j++;
            }break;
          case newarray:
            print_newarray(code_attribute->code[j]);
            j++;
            break;
          case multianewarray:
            {
              u1 byte1 = code_attribute->code[i];
              u1 byte2 = code_attribute->code[i+1];
              u1 dim = code_attribute->code[i + 2];
              u2 index = (byte1 << 8) | byte2;
              str = get_utf8(class_file, index);

              if (!str.empty()) {
                std::cout << " #" << std::dec << index << " " << str;
                std::cout << " dim " << (int) dim;
              }
              j++;
            }break;
          case anewarray:
          case checkcast: 
          case getfield: 
          case getstatic:
          case instanceof: 
          case invokespecial: 
          case invokestatic:
          case invokevirtual:
          case ldc_w: 
          case ldc2_w: 
          case putfield:
          case putstatic:
            {
              u1 byte1 = code_attribute->code[i];
              u1 byte2 = code_attribute->code[i + 1];
              u2 index = (byte1 << 8) | byte2;
              std::cout << " #" << std::dec << index << " " << get_utf8(class_file, index);

              i++;
              j++;
            }break;
          case GOTO: case if_acmpeq:  case if_acmpne:  case if_icmpeq: case if_icmpne: 
          case if_icmplt: case if_icmpge: case if_icmpgt: case if_icmple: case iifeq: case ifne:
          case iflt: case ifge: case ifgt: case ifle: case ifnonull: case ifnull: case jsr:
            {
              u1 branchbyte1 = code_attribute->code[i];
              u1 branchbyte2 = code_attribute->code[i + 1];
              u2 address = (branchbyte1 << 8) | branchbyte2;
              printf("\t%d", address);
              i++;
              j++;
            }break;
          default:
            printf(" 0x%x", code_attribute->code[j]);
            break;
        }
    }
    printf("\n");
  }
  printf("\n");
}