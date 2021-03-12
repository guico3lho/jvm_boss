#include "file_reader.hpp"

Class_file_format read_class_file(std::string filename) {
  FILE *file = fopen(filename.c_str(), "rb");

  // fecha o programa de leitor/exibidor caso o arquivo .class não exista
  if (file == NULL) {
    printf("Arquivo nao encontrado! Terminando execucao..\n");
    exit(1);
  } 

  Class_file_format class_file;

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
    printf( "\n\nArquivo com versao invalida, Versão máxima: Java SE 8.\n");
    printf("Encerrando programa. \n");
    exit(1);
  }

  // Constant Pool Count
  // Count should actually be interpreted as the maximum index plus one
  class_file.constant_pool_count = read_2_bytes(file);
  std::cout << "Constant_pool_count:  " <<class_file.constant_pool_count << std::endl;

  // Constant Pool Table
  // All indexes are 16-bit - 2 bytes
  // Index 1 refers to first constant in the table (index 0 is invalid)
  // The number of constants in the constant pool table is not actually the same as the constant pool count
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
  if (DEBUG) std::cout << "Class File: " << class_name << std::endl;

  fclose(file);

  return class_file;
}
