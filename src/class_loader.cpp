#include "class_loader.hpp"

std::map<std::string, Class_Loader*> loaded_classes;
std::map<std::string, Class_Loader*> static_classes;

Class_Loader* load_class_memory(Class_File class_file) {
  // Cp_Info *cp_info = (Cp_Info*) malloc(sizeof(Cp_Info));

  Class_Loader *class_loader = (Class_Loader*) malloc(sizeof(Class_Loader));
  class_loader->class_file = class_file;

  std::string class_name = get_cp_info_utf8(class_file, class_file.this_class);
  class_loader->class_name = &class_name;
  if (DEBUG) std::cout << "Classe estatica " << class_name << " carregada na memoria!\n";

  loaded_classes.insert((std::pair<std::string, Class_Loader*>(class_name, class_loader)));
  static_classes.insert((std::pair<std::string, Class_Loader*>(class_name, class_loader)));

  class_loader->class_fields = new std::map<std::string, Operand*>();
  // load_class_var(class_loader);s

  if (DEBUG) std::cout << "Classess carregadas na memoria!\n";

  return class_loader;
}