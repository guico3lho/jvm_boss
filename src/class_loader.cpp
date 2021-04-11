#include "class_loader.hpp"
#include "frame.hpp"

std::map<std::string, Class_Loader*> loaded_classes;
std::map<std::string, Class_Loader*> static_classes;
std::string current_path_folder_inter = "test";

Class_Loader* load_class_memory(Class_File class_file) {

  Class_Loader *class_loader = (Class_Loader*) malloc(sizeof(Class_Loader));
  class_loader->class_file = class_file;

  std::string class_name = get_cp_info_utf8(class_file, class_file.this_class);
  class_loader->class_name = &class_name;
  if (DEBUG) std::cout << "Classe estatica " << class_name << " carregada na memoria!\n";

  loaded_classes.insert((std::pair<std::string, Class_Loader*>(class_name, class_loader)));
  static_classes.insert((std::pair<std::string, Class_Loader*>(class_name, class_loader)));

  class_loader->class_fields = new std::map<std::string, Operand*>();
  load_class_var(class_loader);

  if (DEBUG) std::cout << "Classess carregadas na memoria!\n";

  return class_loader;
}

void load_class_var(Class_Loader *class_loader) {
  // Encontra o super_class da classe atual

  class_loader->class_fields = new std::map<std::string, Operand*>();
  Class_File current_class = class_loader->class_file;
  Cp_Info &super_class = current_class.constant_pool[current_class.super_class];

  std::string super_class_name = get_cp_info_utf8(current_class, super_class.Class_Info.class_name);
  if (DEBUG) std::cout << "Super Classe " << super_class_name << " carregada na memoria!\n";

  do {
    for (int i = 0; i < current_class.fields_count; i++) {
      Field_Info &field_add = current_class.fields[i];

      std::string name_field = get_cp_info_utf8( current_class, field_add.name_index);
      std::string type_variable = get_cp_info_utf8(current_class, field_add.descriptor_index);

      (*class_loader->class_fields)[name_field] = check_string_create_type(type_variable);
    }

    if (super_class_name != "java/lang/Object" && super_class_name != "")
      current_class = get_class_info_and_load_not_exists(super_class_name);

  } while (super_class_name != "java/lang/Object");
}

Class_File get_class_info_and_load_not_exists(std::string class_path) {
  // Carrega na memória o path do super_class da classe anterior.

  Class_Loader *class_loader = static_classes[class_path];

  std::cout << "Procurando .class de nome: " << class_path << std::endl;

  if (class_loader == NULL) {
    // verifica se a classe está no mesmo diretorio atual
    std::string filepath = current_path_folder_inter + class_path + ".class";
    Class_File class_file = read_class_file(filepath);
    class_loader = load_class_memory(class_file);
  }

  return class_loader->class_file;
}




