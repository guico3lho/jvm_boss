#include "file_printer.hpp"
#include "interpreter.hpp"

int main(int argc, char* argv[]) {

  Class_File class_file;

  if (argc != 3) {
    std::cout 
      << "Comando incorreto!\n"
      << "Comando leitor/exibidor: -e arquivo.class\n";
  } else {
    std::string option = argv[1], filename = argv[2];

    // leitor/exibidor
    if(option == "-e") {
      class_file = read_class_file(filename);
      print_basic_info(filename, class_file);
      print_constant_pool(class_file);
      print_interfaces(class_file);
      print_fields(class_file);
      print_methods(class_file);
      print_attributes(class_file);
      freeClass(class_file);
    }

    // interpretador
    if(option == "-i") {
      std::cout << "\n----------Modo Interpretador----------\n\n";
      execute(class_file);
    }
  }

  std::cout << "\n\nTerminou execucao\n";
  return 0;
}