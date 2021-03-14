#include "file_reader.hpp"

Class_File_Format read_class_file(std::string filename) {
  FILE *file = fopen(filename.c_str(), "rb");

  // fecha o programa de leitor/exibidor caso o arquivo .class não exista
  if (file == NULL) {
    printf("Arquivo nao encontrado! Terminando execucao..\n");
    exit(1);
  } 

  Class_File_Format class_file;

  class_file.magic_number = read_4_bytes(file); 

  if(class_file.magic_number != 0xCAFEBABE){
    printf("Arquivo com magic numebr invalido. \n");
    printf("Encerrando programa. \n");
    exit(1);
  }

  std::cout << "\n\nFilename:             " << filename << std::endl;
  printf("Magic Number:         0x%0X\n", class_file.magic_number);

  class_file.minor_version = read_2_bytes(file);
  printf("Minor Version:        %0X\n", class_file.minor_version);

  class_file.major_version = read_2_bytes(file);
  std::cout << "Major Version:        " << class_file.major_version << std::endl;

  if (class_file.major_version > 52) {
    printf( "\n\nArquivo com versao invalida - Versão máxima: Java SE 8.\n");
    printf("Encerrando programa. \n");
    exit(1);
  }

  //* Constant Pool Count
  // Count should actually be interpreted as the maximum index plus one
  class_file.constant_pool_count = read_2_bytes(file);
  std::cout << "\n\nConstant Pool Count:  " <<class_file.constant_pool_count << std::endl;

  class_file.constant_pool = (Cp_Info*) malloc ((class_file.constant_pool_count - 1) * sizeof(Cp_Info));
  read_cp_info(file, &class_file);

  class_file.access_flags = read_2_bytes(file);
  printf("Access Flags:         0x%0X\n", class_file.access_flags);

  class_file.this_class = read_2_bytes(file);
  std::cout << "This Class:           " << class_file.this_class << std::endl;

  get_cp_info_class_name(filename, &class_file);

  class_file.super_class = read_2_bytes(file);
  std::cout << "Super Class:          " << class_file.super_class << std::endl;

  //* Interfaces
  class_file.interfaces_count = read_2_bytes(file);
  std::cout << "Interfaces Count:     " << class_file.interfaces_count << std::endl;

  class_file.interfaces = (Interface_Info*) malloc(class_file.interfaces_count * sizeof(Interface_Info));
  read_interface_info(file, &class_file);

  //* Fields
  class_file.fields_count = read_2_bytes(file);
  std::cout << "Fields Count:         " << class_file.fields_count << std::endl;
  class_file.fields = (Field_Info*) malloc(class_file.fields_count * sizeof(Field_Info));
  read_field_info(file, &class_file);

  //* Methods
  // class_file.methods_count = read_2_bytes(file);
  // if (DEBUG) std::cout << "\nmethods count " << class_file.methods_count << std::endl;
  // class_file.methods = (MethodInfo*) malloc(class_file.methods_count * sizeof(MethodInfo));
  // method_info->read(class_file, file);
  // if (DEBUG) std::cout << "method read\n";

  //* Attributes
  // class_file.attributes_count = read_2_bytes(file);
  // class_file.attributes = (AttributeInfo*)malloc(
  //                       class_file.attributes_count * sizeof(AttributeInfo));
  // attribute_info->read(class_file, file);
  // if (DEBUG) std::cout << "attribute read\n";

  fclose(file);

  return class_file;
}


