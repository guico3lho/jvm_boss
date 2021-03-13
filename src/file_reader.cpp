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

  std::cout << "Filename:             " << filename << std::endl;
  printf("Magic Number:         0x%0X\n", class_file.magic_number);

  class_file.minor_version = read_2_bytes(file);
  printf("Minor Version:        %0X\n", class_file.minor_version);

  class_file.major_version = read_2_bytes(file);
  std::cout << "Major Version:        " << class_file.major_version << std::endl;

  if (class_file.major_version > 52){
    printf( "\n\nArquivo com versao invalida - Versão máxima: Java SE 8.\n");
    printf("Encerrando programa. \n");
    exit(1);
  }

  // Constant Pool Count
  // Count should actually be interpreted as the maximum index plus one
  class_file.constant_pool_count = read_2_bytes(file);
  std::cout << "Constant Pool Count:  " <<class_file.constant_pool_count << std::endl;

  class_file.constant_pool = (Cp_Info*) malloc ((class_file.constant_pool_count - 1) * sizeof(Cp_Info));

  read_cp_info(file, &class_file);
  if (DEBUG) std::cout << "Constant Pool info read -------\n";

  class_file.access_flags = read_2_bytes(file);
  printf("Access Flags:         0x%0X\n", class_file.access_flags);

  class_file.this_class = read_2_bytes(file);
  std::cout << "This Class:           " << class_file.this_class << std::endl;

  // Lê o nome da classe no CP e converte pra String
  std::string class_name = get_utf8_constant_pool(class_file.constant_pool, class_file.this_class - 1);

  // Adiciona a extensão '.class' ao nome da classe
  class_name += ".class";
  if (DEBUG) std::cout << "CLASS NAME:           " << class_name << std::endl;

  std::size_t backslash_index = filename.find_last_of("/\\");
  std::string class_filename = filename.substr(backslash_index + 1);
  if (DEBUG) std::cout << "Filename:             " << class_filename << std::endl;

  // Se o nome do arquivo é diferente do nome da classe
  if (class_filename != class_name) {
    printf("O nome do arquivo nao corresponde ao da classe!\n");
    exit(1);
  }

  class_file.super_class = read_2_bytes(file);

  class_file.interfaces_count = read_2_bytes(file);
  class_file.interfaces = (Interface_Info*) malloc(class_file.interfaces_count * sizeof(Interface_Info));
  read_interface_info(file, &class_file);
  if (DEBUG) std::cout << "interface read\n";

  class_file.fields_count = read_2_bytes(file);
  class_file.fields = (Field_Info*) malloc(class_file.fields_count * sizeof(Field_Info));
  read_field_info(file, &class_file);
  if (DEBUG) std::cout << "field read\n";

  // class_file.methods_count = read_2_bytes(file);
  // if (DEBUG) std::cout << "\nmethods count " << class_file.methods_count << std::endl;
  // class_file.methods = (MethodInfo*) malloc(
  //                             class_file.methods_count * sizeof(MethodInfo));
  // method_info->read(class_file, file);
  // if (DEBUG) std::cout << "method read\n";

  // class_file.attributes_count = read_2_bytes(file);
  // class_file.attributes = (AttributeInfo*)malloc(
  //                       class_file.attributes_count * sizeof(AttributeInfo));
  // attribute_info->read(class_file, file);
  // if (DEBUG) std::cout << "attribute read\n";

  fclose(file);

  return class_file;
}
