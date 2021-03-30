#include "utils.hpp"


void print_command_error() {
  std::cout 
    << "\nComando incorreto!\n"
    << "Comando leitor/exibidor: -e test/arquivo.class\n"
    << "Comando para interpretador: -i test/arquivo.class\n"
    << "Encerrando programa.\n";
    exit(1);
}