/** 
 * @file main.cpp
 * @brief Arquivo principal do programa JVM.
 *
 * Universidade de Brasília
 *
 * Software Básico - 2020/2
 * Professor Macelo Ladeira
 *
 * Projeto JVM
 *
 * Executável: ./jvm_boss.exe
 * Comando Leitor/Exibidor: -e nomedoarquivo.class
 * Comando Interpretador: -i nomedoarquivo.class
 *
 * @author Ariel                             17/0099776
 * @author Guilherme Coelho Minervino        16/0123046
 * @author Gustavo Antonio Souza de Barros   18/0064487
 * @author Luís Vinicius Capelletto          16/0134544
 * @author Mayara Chew Marinho               18/0025210
 *
 * @bug No know bugs.
 */

#include "utils.hpp"
#include "interpreter.hpp"
#include "file_printer.hpp"

int main(int argc, char* argv[]) {

  std::string option = argv[1], file = argv[2];

  if(option != "-e" && option != "-i") {
    print_command_error();
  }

  Class_File class_file = read_class_file(file);

  // leitor/exibidor
  if(option == "-e") {
    std::cout << "----------Modo Leitor/Exibidor----------\n\n";
    print_basic_info(file, class_file);
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

  std::cout << "\n\nTerminou execucao\n";
  return 0;
}