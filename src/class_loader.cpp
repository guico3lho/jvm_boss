#include "class_loader.hpp"
#include "frame.hpp"

/**
 * @brief Carrega variáveis com informações do .class
 * @param *class_loader ponteiro para classes carregadas em memoria
 * @return void
 */
void load_class_var(Class_Loader *class_loader) {

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



