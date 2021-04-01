#include "utils.hpp"

char *intToHex(int integer) {
    char *hex_string;
    hex_string = (char*) malloc(30 * sizeof(char));

void print_command_error() {
  std::cout 
  << "\nComando incorreto!\n"
  << "Comando leitor/exibidor: -e test/arquivo.class\n"
  << "Comando para interpretador: -i test/arquivo.class\n"
  << "Encerrando programa.\n";
  exit(1);
}

void freeClass(Class_File class_file){

  if(class_file.constant_pool) {
    for(int i = 1;i<class_file.constant_pool_count;++i){
      if(class_file.constant_pool[i].tag == CONSTANT_UTF8){
      free(class_file.constant_pool[i].Utf8_Info.UTF8_bytes);
      }
    }
    free(class_file.constant_pool);
  }
  if(class_file.interfaces)
    free(class_file.interfaces);

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
  //free(class_file);
}

void freeAttribute(Attribute_Info* attr,u4 size){
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
      freeInnerClass(attr[i].inner_class,1);
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

void freeInnerClass(Inner_Class_Attribute* inner,u4 size){
  for (int i = 0; i < (int)size; ++i) {
  if(inner[i].inner_class_data){
    freeInnerClass(inner[i].inner_class_data,inner[i].number_of_classes);
  }
  }
  free(inner);
}