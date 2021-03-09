#include "file_reader.hpp"

void read_class_file(std::string filename) {
  FILE *file = fopen(filename.c_str(), "rb");

  // fecha o programa de leitor/exibidor caso o arquivo .class não exista
  if (file == NULL) {
    printf("Arquivo não encontrado. Fechando a JVM.\n");
    exit(1);
  } 

  u4 magic_number = read_4_bytes(file); 

  if(magic_number != 0xCAFEBABE){
    printf("Arquivo com magic numebr inválido. \n");
    printf("Encerrando programa. \n");
    exit(1);
  }

  std::cout << "Filename:             " << filename << std::endl;
  std::cout << "magic_number:         " << magic_number << std::endl;
  printf("Magic Number:         0x%0X\n", magic_number);

  u2 minor_version = read_2_bytes(file);
  printf("Minor Version:        %0X\n", minor_version);

  u2 major_version = read_2_bytes(file);
  std::cout << "Major Version:        " << major_version << std::endl;

  if (major_version > 52){
    printf( "\n\nArquivo com versao invalida.\n");
    printf("Encerrando programa. \n");
    exit(1);
  }

  fclose(file);
}