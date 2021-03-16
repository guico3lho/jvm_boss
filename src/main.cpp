#include "../include/Class_File.h"
#include "../include/FileDealer.h"


int main(int argc, char* argv[]) {

 

  if (argc != 3) {
    std::cout 
      << "Comando incorreto!\n"
      << "Comando leitor/exibidor: -e arquivo.class\n";
  } else {
    std::string command = argv[1], filename = argv[2];

    // leitor/exibidor
    if(command == "-e") {
      std::cout << "Modo leitor e exibidor!" << std::endl;
      Class_File classFile(filename);
      std::cout << classFile;

    }
  }

  std::cout << "\n\nTerminou execucao";
  return 0;
}