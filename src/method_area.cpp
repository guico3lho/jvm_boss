#include "method_area.hpp"

Method_Area *method_area = new Method_Area();
/**
 * @brief Lê e armazena classes no method_area
 * @param class_file
 * @return Method_Area*
 */

Method_Area *load_class_memory(Class_File class_file) {
  Class_Container *class_container = new Class_Container();
  class_container->class_file = class_file;

  string class_name = get_cp_info_utf8(class_file, class_file.this_class); 
  if (DEBUG) std::cout << "Classe " << class_name << " carregada na memoria!\n";

  method_area->loaded_classes.insert((std::pair<std::string, Class_Container *>(class_name, class_container))); 
  method_area->static_classes.insert((std::pair<std::string, Class_Container *>(class_name, class_container))); 

  class_container->class_fields = new std::map<std::string, Operand *>();
  // NOTE: Quando tiver chegado aqui, armazena o .class atual e o seu nome no class_container;
  load_class_variables(class_container); 

  if (DEBUG) std::cout << "Classes carregadas na memoria!\n";

  return method_area;
}

/**
 * @brief Carrega variáveis com informações do .class
 * @param class_container ponteiro para classes carregadas em memoria
 * @return void
 */
void load_class_variables(Class_Container *class_container) {
  Class_File current_class = class_container->class_file;
  Cp_Info super_class = current_class.constant_pool[current_class.super_class];

  string super_class_name = get_cp_info_utf8(current_class, super_class.Class.class_name);
  if (DEBUG) cout << "Super Classe " << super_class_name << " carregada na memoria!\n";

  do {
    super_class_name = get_cp_info_utf8(current_class, current_class.super_class);

    for (int i = 0; i < current_class.fields_count; i++) {
      Field_Info field_info = current_class.fields[i];

      string field_name = get_cp_info_utf8(current_class, field_info.name_index);
      string var_type = get_cp_info_utf8(current_class, field_info.descriptor_index);

      (*class_container->class_fields)[field_name] = check_string_create_type(var_type);
    }

    if (super_class_name != "java/lang/Object" && super_class_name != "") {
      current_class = load_parent_classes(super_class_name);
    }

  } while (super_class_name != "java/lang/Object");
}
/**
 * @brief Carrega outro .class se o arquivo estiver no mesmo diretório.
 * @param class_path nome do próximo arquivo .class a ser carregado
 * @return Class_File estrutura de dados do arquivo .class a ser carregado
 */
Class_File load_parent_classes(std::string class_path) {
  if (DEBUG) std::cout << "Class Path: " << class_path << "\n";

  Class_Container *class_container = new Class_Container();
  // Class_Container *class_container = method_area->static_classes[class_path];
  std::cout << "Procurando .class de nome: " << class_path << std::endl;

  // verifica se a classe está no mesmo diretorio atual
  std::string current_path_folder_inter = "test/class/";

  std::string filepath = current_path_folder_inter + class_path + ".class";
  class_container->class_file = read_class_file(filepath);
  std::string class_name = get_cp_info_utf8(class_container->class_file, class_container->class_file.this_class);

  method_area = load_class_memory(class_container->class_file);

  return class_container->class_file;
}


/**
 * @brief Encontra a classe estática
 * @param class_name da classe a ser retornada a referencia
 * @return Class_Container* ponteiro da referencia da classe
 */
Class_Container *get_static_class(std::string class_name) {
  return method_area->static_classes[class_name];
}

/**
 * @brief Get the static field of class object
 * 
 * @param class_name 
 * @param field_name 
 * @return Operand* 
 */
Operand *get_static_field_of_class(std::string class_name, std::string field_name) {
  Class_Container *class_container = method_area->static_classes.at(class_name);
  if (class_container != NULL)
    return class_container->class_fields->at(field_name);
  return NULL;
}

/**
 * @brief Cria um ponteiro de Operand e o tipo é decidido pela string recebida
 * @param type_string string que varia de acordo com o tipo
 * @return Operand* novo ponteiro para Operand
 */
Operand *check_string_create_type(std::string type_string) {
  Operand *new_type = (Operand *)malloc(sizeof(Operand));

  switch (type_string.c_str()[0])
  {
  case 'I':
    if (DEBUG) printf("Criando operando tipo Inteiro\n");
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
    if (DEBUG) printf("Criando operando tipo Array\n");
    new_type->tag = CONSTANT_ARRAY;
    new_type->array_type = new Array_Type();
    new_type->array_type->array = new std::vector<Operand *>();
    break;

  case 'P':
    new_type->tag = CONSTANT_EMPTY;
    break;

  case CONSTANT_STRING:
    new_type->tag = CONSTANT_STRING;
    new_type->type_string = new string("");
    break;

  case 'L': // Tipo Classe
    if (type_string == "Ljava/lang/Integer;") {
      new_type->tag = CONSTANT_INT;
      new_type->type_int = 0;
    }

    if (type_string == "Ljava/lang/String;") {
      if (DEBUG)
        cout << "Class: Ljava/lang/String;\n";
      new_type->tag = CONSTANT_STRING;
      new_type->type_string = new string("");
    } else {
      new_type->tag = CONSTANT_CLASS;
      new_type->class_container = (Class_Container*) malloc(sizeof(Class_Container));

      std::string class_realname = type_string.substr(1, type_string.size());
      if (DEBUG) std::cout << "Nome da Classe: " << class_realname << "\n";

      Class_File class_info = load_parent_classes(class_realname);
      new_type->class_container->class_file = class_info;

      load_class_variables(new_type->class_container);
    }
    break;
  }
  return new_type;
}

/** @brief Encontra metodo main da super classe final.
 *  @param method_area
 *  @return MethodInfo*
 */
Method_Info *find_main(Method_Area *method_area) { 
  Class_File class_file = method_area->loaded_classes.begin()->second->class_file;
  for (int i = 0; i < class_file.methods_count; i++) {
    Method_Info *method = class_file.methods + i;
    string method_name = get_cp_info_utf8(class_file, method->name_index);
    if (DEBUG)
      cout << "Nome do metodo: " << method_name << " carregado na memoria\n";

    if (method_name == "main") {
      string method_descriptor = get_cp_info_utf8(class_file, method->descriptor_index); // (method_area, method)
      if (DEBUG)
        cout << "Descricao do metodo main econtrado: " << method_descriptor << "\n";

      if (method_descriptor == "([Ljava/lang/String;)V") {
        if (DEBUG)
          cout << "METHOD MAIN ENCONTRADO!\n";
        return method;
      }
    }
  }

  cout << "Erro: Class File inserido nao possui metodo main." << std::endl;
  exit(1);
}
