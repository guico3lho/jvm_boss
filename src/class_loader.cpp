/**
 * @file class_loader.cpp
 * @brief Arquivo com funções do Class Loader da JVM
*/

#include "class_loader.hpp"

std::map<std::string, Class_Loader*> loaded_classes;
std::map<std::string, Class_Loader*> static_classes;

/**
 * @brief Carrega classes para a memória.
 */

Class_Loader* load_class_memory(Class_File class_file) {
  Class_Loader *class_loader = (Class_Loader*) malloc(sizeof(Class_Loader));
  class_loader->class_file = class_file;

  std::string class_name = get_cp_info_utf8(class_file, class_file.this_class);
  class_loader->class_name = &class_name;
  if (DEBUG) std::cout << "Classe estatica " << class_name << " carregada na memoria!\n";

  // NOTE: What the lines above are doing?
  loaded_classes.insert((std::pair<std::string, Class_Loader*>(class_name, class_loader)));
  static_classes.insert((std::pair<std::string, Class_Loader*>(class_name, class_loader)));

  class_loader->class_fields = new std::map<std::string, Operand*>();
  load_class_var(class_loader);

  if (DEBUG) std::cout << "Classes carregadas na memoria!\n";

  return class_loader;
}

/**
 * @brief Carrega variáveis com informações do .class
 * @param *Class_Loader ponteiro para classes carregadas em memoria
 * @return void
 */
void load_class_var(Class_Loader *class_loader) {
  Class_File current_class = class_loader->class_file;
  Cp_Info &super_class = current_class.constant_pool[current_class.super_class];

  std::string super_class_name = get_cp_info_utf8(current_class, super_class.Class.class_name);
  if (DEBUG) std::cout << "Super Classe " << super_class_name << " carregada na memoria!\n";

  do {
    super_class_name = get_cp_info_utf8(current_class, current_class.super_class);

    for (int i = 0; i < current_class.fields_count; i++) {
      Field_Info &field_info = current_class.fields[i];

      std::string field_name = get_cp_info_utf8( current_class, field_info.name_index);
      std::string var_type = get_cp_info_utf8(current_class, field_info.descriptor_index);

      (*class_loader->class_fields)[field_name] = check_string_create_type(var_type);
    }

    if (super_class_name != "java/lang/Object" && super_class_name != "") {
      if (DEBUG) std::cout << "Escopo de load_class_var!!" << "\n";
      current_class = get_class_info_and_load_not_exists(super_class_name);
    }

  } while(super_class_name != "java/lang/Object");
}

/**
 * @brief Carrega outro .class se o arquivo estiver no mesmo diretório.
 * @param c_path nome do próximo arquivo .class a ser carregado
 * @return JavaClass estrutura de dados do arquivo .class a ser carregado
 */
Class_File get_class_info_and_load_not_exists(std::string class_path) {
  if (DEBUG) std::cout << "Class Path: " << class_path << "\n";

  Class_Loader *class_loader = static_classes[class_path];
  std::cout << "Procurando .class de nome: " << class_path << std::endl;

  if (class_loader == NULL) {
    // verifica se a classe está no mesmo diretorio atual
    std::string current_path_folder_inter = "test";

    std::string filepath = current_path_folder_inter + class_path + ".class";
    Class_File class_file = read_class_file(filepath);
    class_loader = load_class_memory(class_file);
  }

  return class_loader->class_file;
}

/**
 * @brief Retorna a classe estática
 * @param std::string nome da classe a ser retornada a referencia
 * @return ClassInstance* ponteiro da referencia da classe
 */
Class_Loader* get_static_class(std::string class_name){
  return static_classes[class_name];
}

/**
 * @brief Get the static field of class object
 * 
 * @param class_name 
 * @param field_name 
 * @return Operand* 
 */
Operand* get_static_field_of_class(std::string class_name, std::string field_name) {
    Class_Loader *class_loader = static_classes.at(class_name);
    if (class_loader != NULL) return class_loader->class_fields->at(field_name);
    return NULL;
}

/**
 * @brief Cria um ponteiro de Operand e o tipo é decidido pela string recebida
 * @param type_string string que varia de acordo com o tipo
 * @return Operand* novo ponteiro para Operand
 */
Operand* check_string_create_type(std::string type_string) {
  Operand *new_type = (Operand*)malloc(sizeof(Operand));

  switch (type_string.c_str()[0]) {
    case 'I':
      new_type->tag = CONSTANT_INT;
      new_type->type_int = 0;
      break;
    case 'F':
      new_type->tag = CONSTANT_FLOAT;
      new_type->type_float = 0;
      break;
    case 'J':
      new_type->tag = CONSTANT_LONG;
      new_type->type_long = 0;
      break;
    case 'D':
      new_type->tag = CONSTANT_DOUBLE;
      new_type->type_double = 0;
      break;
    case 'Z':
      new_type->tag = CONSTANT_BOOL;
      new_type->type_bool = 0;
      break;
    case 'B':
      new_type->tag = CONSTANT_BYTE;
      new_type->type_byte = 0;
      break;
    case 'C':
      new_type->tag = CONSTANT_CHAR;
      new_type->type_char = 0;
      break;
    case 'S':
      new_type->tag = CONSTANT_SHORT;
      new_type->type_short = 0;
      break;
    case '[':
    // if (DEBUG) printf("Entered [ case\n");
      new_type->tag = CONSTANT_ARRAY;
      new_type->array_type = (Array_Type*) malloc(sizeof(Array_Type));
      new_type->array_type->array = new std::vector<Operand*>();
      break;
    case 'P':
      new_type->tag = CONSTANT_EMPTY;
      break;
    case CONSTANT_STRING:
      new_type->tag = CONSTANT_STRING;
      new_type->type_string = new std::string("");
      break;
    case 'L':
      if (type_string == "Ljava/lang/String;") {
        new_type->tag = CONSTANT_STRING;
        new_type->type_string = new std::string("");
      } else {
        new_type->tag = CONSTANT_CLASS;
        new_type->class_loader = (Class_Loader*) malloc(sizeof(Class_Loader));

        std::string class_realname = type_string.substr(1, type_string.size());
        if (DEBUG) std::cout << "Escopo de check_string_create_type!!" << "\n";
        Class_File info_class = get_class_info_and_load_not_exists(class_realname);

        new_type->class_loader->class_file = info_class;
        new_type->class_loader->class_name = &class_realname;

        load_class_var(new_type->class_loader);
      }
      break;
  }
  return new_type;
}