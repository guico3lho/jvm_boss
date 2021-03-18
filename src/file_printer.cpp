#include "file_printer.hpp"

void print_basic_info(std::string filename, Class_File_Format class_file) {
  std::cout << "------------ Basic Info ------------" << std::endl;
  std::cout << "Filename:             " << filename << std::endl;
  printf("Magic Number:         0x%0X\n", class_file.magic_number);
  printf("Minor Version:        %d\n", class_file.minor_version);
  printf("Major version:        %d\n", class_file.major_version);
  printf("Contanst pool count:  %d\n", class_file.constant_pool_count);
  printf("Access flags:         0x%.4x\n", class_file.access_flags);
  printf("This class:           cp_info #%d < ", class_file.this_class);

  std::cout << get_cp_info_utf8(class_file.constant_pool,
  class_file.constant_pool[class_file.this_class - 1].class_name - 1)
  << " >";

  printf("\nSuper class:          cp_info #%d < ", class_file.super_class);
  std::cout << get_cp_info_utf8(class_file.constant_pool, 
  class_file.constant_pool[class_file.super_class - 1].class_name - 1)
  << " >";

  printf("\nInterface count:      %d\n", class_file.interfaces_count);
  printf("Field count:          %d\n", class_file.fields_count);
  printf("Methods count:        %d\n", class_file.methods_count);
  printf("Attributes count:     %d\n", class_file.attributes_count);
}