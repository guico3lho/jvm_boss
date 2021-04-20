/**
 * @file class_file.cpp
 * @brief Arquivo de funções relacionados com a leitura de dados do arquivo bytecode (.class)
*/

#include "class_file.hpp"

/**
 * @brief Função de leitura dos dados do arquivo .class 
 * 
 * @param filename 
 * @return Class_File 
 */
Class_File read_class_file(std::string filename) {
  FILE *file = fopen(filename.c_str(), "rb");

  // Terminando execucao caso arquivo .class nao exista
  if (file == NULL) {
    printf("Arquivo nao encontrado! Terminando execucao..\n");
    exit(1);
  } 

  Class_File class_file;
  class_file.magic_number = read_4_bytes(file); 

  if(class_file.magic_number != 0xCAFEBABE){
    printf("Arquivo com magic numebr invalido. \n");
    printf("Encerrando programa.\n");
    exit(1);
  }

  if (DEBUG) std::cout << "\n\nFilename:             " << filename << std::endl;
  if (DEBUG) printf("Magic Number:         0x%0X\n", class_file.magic_number);

  class_file.minor_version = read_2_bytes(file);
  if (DEBUG) printf("Minor Version:        %0X\n", class_file.minor_version);

  class_file.major_version = read_2_bytes(file);
  if (DEBUG) std::cout << "Major Version:        " << class_file.major_version << std::endl;

  if (class_file.major_version > 52) {
    printf( "\n\nArquivo com versao invalida - Versão máxima: Java SE 8.\n");
    printf("Encerrando programa.\n");
    exit(1);
  }

  //* Constant Pool Count = max_index + 1
  class_file.constant_pool_count = read_2_bytes(file);
  if (DEBUG) std::cout << "\nConstant Pool Count:  " << class_file.constant_pool_count << std::endl;
  class_file.constant_pool = (Cp_Info*) malloc ((class_file.constant_pool_count ) * sizeof(Cp_Info));
  read_cp_info(file, class_file);

  class_file.access_flags = read_2_bytes(file);
  if (DEBUG) printf("Access Flags:         0x%0X\n", class_file.access_flags);

  class_file.this_class = read_2_bytes(file);
  if (DEBUG) std::cout << "This Class:           " << class_file.this_class << std::endl;
  
  get_cp_info_class_name(filename, class_file); 

  class_file.super_class = read_2_bytes(file);
  if (DEBUG) std::cout << "Super Class:          " << get_cp_info_utf8(class_file, class_file.super_class) << std::endl;

  //* Interfaces
  class_file.interfaces_count = read_2_bytes(file);
  if (DEBUG) std::cout << "Interfaces Count:     " << class_file.interfaces_count << std::endl;
  class_file.interfaces = (Interface_Info*) malloc(class_file.interfaces_count * sizeof(Interface_Info));
  read_interface_info(file, &class_file);

  //* Fields
  class_file.fields_count = read_2_bytes(file);
  if (DEBUG) std::cout << "Fields Count:         " << class_file.fields_count << std::endl;
  class_file.fields = (Field_Info*) malloc(class_file.fields_count * sizeof(Field_Info));
  read_field_info(file, &class_file);

  //* Methods
  class_file.methods_count = read_2_bytes(file);
  if (DEBUG) std::cout << "Methods count:        " << class_file.methods_count << std::endl;
  class_file.methods = (Method_Info*) malloc(class_file.methods_count * sizeof(Method_Info));
  read_method_info(file, &class_file);

  //* Attributes
  class_file.attributes_count = read_2_bytes(file);
  if (DEBUG) std::cout << "Attributes count:        " << class_file.attributes_count << std::endl;
  class_file.attributes = (Attribute_Info*) malloc(class_file.attributes_count * sizeof(Attribute_Info));
  read_attribute_info(file, &class_file);

  fclose(file);

  return class_file;
}
