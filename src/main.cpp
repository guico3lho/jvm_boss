#include "../include/types.hpp"
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

    }
  }

  std::cout << "\n\nTerminou execucao";
  return 0;
}