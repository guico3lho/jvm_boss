#include "file_reader.hpp"

void read_class_file(std::string filename) {
  FILE *file = fopen(filename.c_str(), "rb");

  // fecha o programa de leitor/exibidor caso o arquivo .class não exista
  if (file == NULL) {
    printf("Arquivo nao encontrado! Terminando execução..\n");
    exit(1);
  } 

  class_File_Format class_file_format;

  class_file_format.magic_number = read_4_bytes(file); 

  if(class_file_format.magic_number != 0xCAFEBABE){
    printf("Arquivo com magic numebr invalido. \n");
    printf("Encerrando programa. \n");
    exit(1);
  }

  std::cout << "Filename:             " << filename << std::endl;
  printf("Magic Number:         0x%0X\n", class_file_format.magic_number);

  class_file_format.minor_version = read_2_bytes(file);
  printf("Minor Version:        %0X\n", class_file_format.minor_version);

  class_file_format.major_version = read_2_bytes(file);
  std::cout << "Major Version:        " << class_file_format.major_version << std::endl;

  if (class_file_format.major_version > 52){
    printf( "\n\nArquivo com versao invalida, Versão máxima: Java SE 8.\n");
    printf("Encerrando programa. \n");
    exit(1);
  }

  // Constant Pool
  class_file_format.constant_pool_count = read_2_bytes(file);
  std::cout << "constant_pool_count:  " << class_file_format.constant_pool_count << std::endl;

  // Constant Pool Table



  fclose(file);
}