/**
 * @file utils.cpp
 * @brief Arquivo com funções de impressão de erros no terminal e liberação de memória.
 */

#include "utils.hpp"

/** 
 * @brief Imprime mensagem de comando incorreto.
 * @param void
 * @return void
 */
void print_command_error() {
  std::cout 
  << "\nComando incorreto!\n"
  << "Comando leitor/exibidor: -e test/arquivo.class\n"
  << "Comando para interpretador: -i test/arquivo.class\n"
  << "Encerrando programa.\n";
  exit(1);
}

/**
 * @brief Converte float no formato IEEE de bits para valor float
 * @param float_bits 
 * @return float 
 */
float float_bits_to_value(u4 float_bits){
  float float_value;
  std::memcpy(&float_value, &float_bits, sizeof(float));
  return float_value;
}

/**
 * @brief Converte valor float para o formato IEEE de bits 
 * @param float_value 
 * @return uint32_t 
 */
u4 float_value_to_bits(float float_value) {
  u4 float_bits = 0;
  memcpy(&float_bits, &float_value, sizeof (float_bits));
  return float_bits;
}

/**
 * @brief Converte double no formato IEEE de bits para valor double
 * @param double_bits 
 * @return double 
 */
double double_bits_to_value(u8 double_bits) {
  double double_value;
  std::memcpy(&double_value, &double_bits, sizeof(double));
  return double_value;
}

/** 
 * @brief Libera a memória alocada para o Class File.
 * @param class_file estrutura Class_File que precisa ser liberada
 * @return void
 */
void freeClass(Class_File class_file){

  if(class_file.constant_pool) {
    for(int i = 1; i < class_file.constant_pool_count; i++){
      if(class_file.constant_pool[i].tag == CONSTANT_UTF8){
        free(class_file.constant_pool[i].Utf8.bytes); 
      }
    }
    free(class_file.constant_pool);
  }

  if(class_file.interfaces) {
    free(class_file.interfaces);
  }

  if(class_file.fields) {
    for (int i = 0; i < class_file.fields_count; ++i) {
      freeAttribute(class_file.fields[i].attributes, class_file.fields[i].atributes_count);
    }
    free(class_file.fields);
  }

  if(class_file.methods) {
    for (int i = 0; i < class_file.methods_count; ++i) {
      freeAttribute(class_file.methods[i].attributes, class_file.methods[i].attributes_count);
    }
    free(class_file.methods);
  }

  if(class_file.attributes) {
    freeAttribute(class_file.attributes, class_file.attributes_count);
  }
  //free(class_file.attributes);
  // free(class_file);
}

/** 
 * @brief Libera a memória alocada para um atributo.
 * @param attr estrutura Attribute que precisa ser liberada
 * @param size tamanho do array de atributos
 * @return void
 */
void freeAttribute(Attribute_Info* attr, u4 size){
  for (int i = 0; i < (int) size; ++i) {
    if(attr[i].source_file){
      free(attr[i].source_file);
    }

    if(attr[i].local_variable_table){
      free(attr[i].local_variable_table->table);
      free(attr[i].local_variable_table);
    }

    if(attr[i].line_number_table){
      free(attr[i].line_number_table->table);
      free(attr[i].line_number_table);
    }

    if(attr[i].info){
      free(attr[i].info);
    }

    if(attr[i].inner_class){
      freeInnerClass(attr[i].inner_class, 1);
    }

    if(attr[i].exception){
      free(attr[i].exception->exception_index_table);
      free(attr[i].exception);
    }

    if(attr[i].const_value){
      free(attr[i].const_value);
    }

    if (attr[i].code){
      free(attr[i].code->code);
      free(attr[i].code->exception_table);
      freeAttribute(attr[i].code->attributes,attr[i].code->attributes_count);
      free(attr[i].code);
    }
  }
  free(attr);
}

/** 
 * @brief Libera a memória de atributos do tipo Inner Class.
 * @param inner estrutura Inner_Class_Attribute que precisa ser liberada.
 * @param size tamanho do array de classes internas.
 * @return void
 */
void freeInnerClass(Inner_Class_Attribute* inner, u4 size){
  for (int i = 0; i < (int)size; ++i) {
    if(inner[i].inner_class_data){
      freeInnerClass(inner[i].inner_class_data,inner[i].number_of_classes);
    }
  }
  free(inner);
}