#include <stdio.h>
#include <iostream>
#include "begin.hpp"
#include "file_reader.hpp"

int main(int argc, char* argv[]) {

  if (argc != 3) {
    std::cout 
      << "Comando incorreto!\n"
      << "Comando para leitor/exibidor : -e arquivo.class\n";
  } else {
    std::string command = argv[1], filename = argv[2];

    // leitor/exibidor
    if(command == "-e") {
      read_class_file(filename);

    }
  }

  std::cout << "\n\nTerminou execucao";
  return 0;
}