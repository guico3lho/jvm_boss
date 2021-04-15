#include "utils.hpp"
#include "interpreter.hpp"
#include "file_printer.hpp"


int main(int argc, char* argv[]) {

  if (argc != 3) {
    print_command_error();
  } else {
    std::string option = argv[1], filename = argv[2];

    if(option != "-e" && option != "-i") {
      print_command_error();
    }

    Class_File class_file;
    class_file = read_class_file(filename);

    // leitor/exibidor
    if(option == "-e") {
      std::cout << "----------Modo Leitor/Exibidor----------\n\n";
      print_basic_info(filename, class_file);
      print_constant_pool(class_file);
      print_interfaces(class_file);
      print_fields(class_file);
      print_methods(class_file);
      print_attributes(class_file);
    }

    // interpretador
    if(option == "-i") {
      std::cout << "\n----------Modo Interpretador----------\n\n";
      execute(class_file);
    }

    freeClass(class_file);
  }

  std::cout << "\n\nTerminou execucao\n";
  return 0;
}