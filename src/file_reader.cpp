#include "file_reader.hpp"

Class_File read_class_file(std::string filename) {
  FILE *file = fopen(filename.c_str(), "rb");

  // Terminando execucao caso arquivo .class nao exista
  if (file == NULL) {
    printf("Arquivo nao encontrado! Terminando execucao..\n");
    exit(1);
  } 

  Class_File class_file;
  class_file.magic_number = read_4_bytes(file); 

  if(class_file.magic_number != 0xCAFEBABE){
    printf("Arquivo com magic_number number invalido. \n");
    printf("Encerrando programa.\n");
    exit(1);
  }

  if (DEBUG) std::cout << "\n\nFilename:             " << filename << std::endl;
  if (DEBUG) printf("Magic Number:         0x%0X\n", class_file.magic_number);

  class_file.minor_version = read_2_bytes(file);
  if (DEBUG) printf("Minor Version:        %0X\n", class_file.minor_version);

  class_file.major_version = read_2_bytes(file);
  if (DEBUG) std::cout << "Major Version:        " << class_file.major_version << std::endl;

  if (class_file.major_version > 52) {
    printf( "\n\nArquivo com versao invalida - Versão máxima: Java SE 8.\n");
    printf("Encerrando programa.\n");
    exit(1);
  }

  //* Constant Pool Count = max_index + 1
  class_file.constant_pool_count = read_2_bytes(file);
  if (DEBUG) std::cout << "\nConstant Pool Count:  " << class_file.constant_pool_count << std::endl;
  class_file.constant_pool = (Cp_Info*) malloc ((class_file.constant_pool_count) * sizeof(Cp_Info));
  read_cp_info(class_file,file);  
  
  class_file.access_flags = read_2_bytes(file);
  if (DEBUG) printf("Access Flags:         0x%0X\n", class_file.access_flags);

  class_file.this_class = read_2_bytes(file);
  if (DEBUG) std::cout << "This Class:           " << class_file.this_class << std::endl;
  
  get_cp_info_class_name(filename, class_file);

  class_file.super_class = read_2_bytes(file);
  if (DEBUG) std::cout << "Super Class:          " << class_file.super_class << std::endl;

  //* Interfaces
  class_file.interfaces_count = read_2_bytes(file);
  if (DEBUG) std::cout << "Interfaces Count:     " << class_file.interfaces_count << std::endl;
  class_file.interfaces = (Interface_Info*) malloc(class_file.interfaces_count * sizeof(Interface_Info));
  read_interface_info(file, &class_file);

  //* Fields
  class_file.fields_count = read_2_bytes(file);
  if (DEBUG) std::cout << "Fields Count:         " << class_file.fields_count << std::endl;
  class_file.fields = (Field_Info*) malloc(class_file.fields_count * sizeof(Field_Info));
  read_field_info(file, &class_file);

  //* Methods
  class_file.methods_count = read_2_bytes(file);
  if (DEBUG) std::cout << "Methods count:        " << class_file.methods_count << std::endl;
  class_file.methods = (Method_Info*) malloc(class_file.methods_count * sizeof(Method_Info));
  read_method_info(file, &class_file);

  //* Attributes
  class_file.attributes_count = read_2_bytes(file);
  if (DEBUG) std::cout << "Attributes count:        " << class_file.attributes_count << std::endl;
  class_file.attributes = (Attribute_Info*) malloc(class_file.attributes_count * sizeof(Attribute_Info));
  read_attribute_info(file, &class_file);

  fclose(file);

  return class_file;
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
            freeInner(attr[i].inner_class,1);
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

void freeInner(Inner_Class_Attribute* inner,u4 size){
    for (int i = 0; i < (int)size; ++i) {
        if(inner[i].inner_class_data){
            freeInner(inner[i].inner_class_data,inner[i].number_of_classes);
        }
    }
    free(inner);
}


