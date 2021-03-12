#include "file_reader.hpp"

int main(int argc, char* argv[]) {

  Class_file_format class_file;

  if (argc != 3) {
    std::cout 
      << "Comando incorreto!\n"
      << "Comando para leitor/exibidor : -e arquivo.class\n";
  } else {
    std::string command = argv[1], filename = argv[2];

    // leitor/exibidor
    if(command == "-e") {
      class_file = read_class_file(filename);

    }
  }

  std::cout << "\n\nTerminou execucao";
  return 0;
}