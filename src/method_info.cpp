/**
 * @file method_info.cpp
 * @brief Arquivo com funções relacionadas a Method.
 */

#include "method_info.hpp"

/** 
 * @brief Lê as informações de method e armazena no Class_File.
 * @param *file ponteiro para o arquivo que vai ser lido.
 * @param *class_file ponteiro para a estrutura Class_File em que as informações vão ser armazenadas.
 * @return void
 */
void read_method_info(FILE *file, Class_File *class_file) {

  for (int i = 0; i < class_file->methods_count; i++) {
    if (DEBUG) printf("\nMethod: %d\n", i);

    class_file->methods[i].access_flags = read_2_bytes(file);
    class_file->methods[i].name_index = read_2_bytes(file);
    class_file->methods[i].descriptor_index = read_2_bytes(file);

    class_file->methods[i].attributes_count = read_2_bytes(file);
    class_file->methods[i].attributes = (Attribute_Info*) malloc(class_file->methods[i].attributes_count * sizeof(Attribute_Info));
    if (DEBUG) std::cout << "attributes_count: " << class_file->methods[i].attributes_count << std::endl;

    for (int j = 0; j < class_file->methods[i].attributes_count; j++) {
      if (DEBUG) std::cout << "Reading Attribute " << j << std::endl;
      class_file->methods[i].attributes[j] = get_attribute_info(file, class_file);
    }
  }
}

/** @brief Encontra metodo main da super classe final.
 *  @param class_file 
 *  @return MethodInfo*
 */
Method_Info* find_main(Class_File class_file) {

  for (int i = 0; i < class_file.methods_count; i++) {
    Method_Info *method = class_file.methods + i;
    std::string method_name = get_cp_info_utf8(class_file, method->name_index);
    if (DEBUG) std::cout << "Nome do metodo: " << method_name << " carregado na memoria\n";

    if (method_name == "main") {
      std::string method_descriptor = get_cp_info_utf8(class_file, method->descriptor_index);
      if (DEBUG) std::cout << "Descricao do metodo main econtrado: " << method_descriptor << std::endl;

      if (method_descriptor == "([Ljava/lang/String;)V") {
        if (DEBUG) std::cout << "METHOD MAIN ENCONTRADO!\n";
        return method;
      }
    }
  }

  std::cout << "Erro: Class File inserido nao possui metodo main." << std::endl;
  exit(1);
}

/**
* @brief Encontra um método pelo nome e descrição.
* @param class_file ponteiro para o classfile atual
* @param method_name string do nome do método a ser buscado
* @param method_descriptor string da descrição do método
* @return MethodInfo* ponteiro para as informações relacionadas ao método
*/
Method_Info *find_method(Class_File class_file, std::string method_name, std::string method_descriptor) {
  for (int i = 0; i < class_file.methods_count; i++) {
    Method_Info *method_info = class_file.methods + i;

    std::string check_method_name = get_cp_info_utf8(class_file, method_info->name_index);
    if (check_method_name == method_name) {
      std::string check_method_descriptor = get_cp_info_utf8(class_file, method_info->descriptor_index);
      if (check_method_descriptor == method_descriptor) return method_info;
    }
  }

  printf("Método não encontrado\n");
  getchar();
  exit(5);
}