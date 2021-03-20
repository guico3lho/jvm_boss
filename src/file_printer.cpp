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

void print_cp_info_utf8(Cp_Info cp_info) {
  std::cout << "CONSTANT_UTF8_info\n";
  std::cout << "\tLength:\t"<< std::dec << cp_info.UTF8_size << std::endl;
  std::cout << "\tBytes:\t"<< cp_info.UTF8_bytes << std::endl;
}

void print_cp_info_int(Cp_Info cp_info) {
  // Valor da constante int, em big-endian
  printf("CONSTANT_INT\n");
  printf("Int Value: %d\n", cp_info.int_bytes);
}

void print_cp_info_float(Cp_Info cp_info) {
  printf("CONSTANT_FLOAT\n");
  float float_value;
  memcpy(&float_value, &(cp_info.float_bytes), sizeof(float));
  // representa o valor da constante float em big-endian, no formato IEEE-754
  printf("Float Value: %lf\n", float_value);
}

void print_cp_info_long(Cp_Info cp_info) {
  printf("CONSTANT_LONG\n");
  // representa uma constante inteira de 8 bytes em big-endian unsigned
  std::cout << "\tHigh:\t0x" << std::hex << cp_info.long_high_bytes << std::endl;
  // printf("\tHigh: 0x%0x\n", cp_info.long_high_bytes);
  printf("\tLow: 0x%0x\n", cp_info.long_low_bytes);
  long read_long_value;
  memcpy(&read_long_value, &(cp_info.long_high_bytes), sizeof(long));
  memcpy(&read_long_value, &(cp_info.long_low_bytes), sizeof(long));
  // ((long) high_bytes << 32) + low_bytes
  printf("\tLong Value: %ld\n", read_long_value);
}

void print_cp_info_double(Cp_Info cp_info) {
  double read_double_value;
  u8 aux;

  printf("CONSTANT_DOUBLE\n");
  std::cout << "\tHigh:\t0x"<< std::hex << cp_info.double_high_bytes << std::endl;
  std::cout << "\tLow:\t0x"<< std::hex << cp_info.double_low_bytes << std::endl;

  // Constante double de 8 bytes em big-endian no formato IEEE-754
  aux = ((u8)cp_info.double_high_bytes << 32) | cp_info.double_low_bytes;
  memcpy(&read_double_value, &aux, sizeof(double));
  std::cout << "\tDouble Value:\t"<< read_double_value << std::endl;
}

void print_cp_info_class(Class_File_Format class_file, Cp_Info cp_info) {
  std::cout << "CONSTANT_CLASS" << std::endl;
  std::cout << "\tName index:\t#" << std::dec << cp_info.class_name << std::endl;
  // exibe nome de uma classe ou interface
  std::cout << "\tClass name:\t" << get_cp_info_utf8(class_file.constant_pool, cp_info.class_name - 1) << std::endl;
}

void print_constant_pool_info(Class_File_Format class_file) {
  std::cout << "\n\n------- Constant Pool -------\n\n";

  for (int i = 0; i < class_file.constant_pool_count-1; i++) {
    std::cout << "\nCP_INFO[" << std::dec << i + 1 << "]" << std::endl;

    switch (class_file.constant_pool[i].tag) {
      case CONSTANT_UTF8:
        print_cp_info_utf8(class_file.constant_pool[i]);
        break;
      case CONSTANT_INT:
        print_cp_info_int(class_file.constant_pool[i]);
        break;
      case CONSTANT_FLOAT:
        print_cp_info_float(class_file.constant_pool[i]);
        break;
      case CONSTANT_LONG:
        print_cp_info_long(class_file.constant_pool[i]);
        break;
      case CONSTANT_DOUBLE:
        print_cp_info_double(class_file.constant_pool[i]);
        break;
      case CONSTANT_CLASS :
        print_cp_info_class(class_file, class_file.constant_pool[i]);
        
      break;
      case CONSTANT_STRING:
        std::cout << "CONSTANT_STRING" << std::endl;

        // representa sequência de caracteres com a qual o objeto String será iniciado
        std::cout << "\tString:\t#" << std::dec << class_file.constant_pool[i].string_bytes;
        std::cout << "\t" << get_cp_info_utf8(class_file.constant_pool,
                              class_file.constant_pool[i].string_bytes - 1) << std::endl;
        break;
      case CONSTANT_FIELD_REF:
        std::cout << "CONSTANT_FIELD_REF" << std::endl;

        // representa nome completo da classe ou interface que contem a declaração desse field
        std::cout << "\tClass index:\t#" << std::dec << class_file.constant_pool[i].field_ref_class_index ;
        std::cout << "\t" << get_cp_info_utf8(class_file.constant_pool,
                          class_file.constant_pool[i].field_ref_class_index - 1) << std::endl;

        // representa um field ou método sem indicar classe ou interface a que pertence
        std::cout << "\tName and Type:\t#" << std::dec << class_file.constant_pool[i].field_ref_name_type_index;
        std::cout << "\t" << get_cp_info_utf8(class_file.constant_pool,
                  class_file.constant_pool[i].field_ref_name_type_index - 1) << std::endl;
        break;
      case CONSTANT_METHOD_REF:
        std::cout << "CONSTANT_METHOD_REF"<< std::endl;

        // representa um método
        std::cout << "\tClass index:\t#"<< class_file.constant_pool[i].method_ref_index;
        // representa nome completo classe que contem a declaração desse método
        std::cout << " \t" << get_cp_info_utf8(class_file.constant_pool,
                              class_file.constant_pool[i].method_ref_index - 1);
        std::cout << std::endl;

        std::cout << "\tName and Type:\t#"<< class_file.constant_pool[i].method_ref_name_and_type;
        // indica nome e descritor do método
        std::cout << "\t" << get_cp_info_utf8(class_file.constant_pool,
                        class_file.constant_pool[i].method_ref_name_and_type - 1);
        std::cout << std::endl;
        break;
      case CONSTANT_INTERFACE_METHOD_REF:
        std::cout << "CONSTANT_INTERFACE_METHOD_REF"<< std::endl;

        // representa nome completo da interface que contem a declaração desse método
        std::cout << "Index:"<< std::endl;
        std::cout << get_cp_info_utf8(class_file.constant_pool,
                      class_file.constant_pool[i].interface_method_ref_index - 1)<< std::endl;

        // indica nome e descritor do método
        std::cout << "Name and Type:"<< std::endl;
        std::cout << get_cp_info_utf8(class_file.constant_pool,
              class_file.constant_pool[i].interface_method_ref_name_type - 1);
        break;
      case CONSTANT_NAME_TYPE:
        std::cout << "CONSTANT_NAME_TYPE:"<< std::endl;

        // printf("Name index: ");
        std::cout << "\tName:\t\t#"<< class_file.constant_pool[i].name_type_index;
        std::cout << "\t" << get_cp_info_utf8(class_file.constant_pool,
                        class_file.constant_pool[i].name_type_index - 1) << std::endl;
        // printf("\nDescriptor index: ");
        std::cout << "\tDescriptor:\t#"<< class_file.constant_pool[i].name_type_descriptor_index;
        std::cout << "\t" << get_cp_info_utf8(class_file.constant_pool,
                  class_file.constant_pool[i].name_type_descriptor_index - 1) << std::endl;
        break;
      case CONSTANT_EMPTY:
        std::cout << "\tLarge numeric continued / empty item"<< std::endl;
        break;
      default:
        printf("Tag %d. Wrong tag number. Shutting down.\n",
                class_file.constant_pool[i].tag);
        exit(1);
    }
    printf("\n");
  }
}