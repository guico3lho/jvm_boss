/**
 * @file cp_info.cpp
 * @brief Arquivo com funções relacionadas à Constant Pool
 */

#include "cp_info.hpp"

/**
 * @brief Lê a constant pool e armazena no class_file
 * @param *file
 * @param class_file
 * @return void
 */
void read_cp_info(FILE *file, Class_File class_file) {
  for (int i = 1; i <  class_file.constant_pool_count; i++) {
    u2 tag = read_1_byte(file);
    class_file.constant_pool[i].tag = tag;

    switch (tag) {
    case CONSTANT_CLASS:
      class_file.constant_pool[i].Class.class_name = read_2_bytes(file);
      break;

    case CONSTANT_FIELD_REF:
      class_file.constant_pool[i].Fieldref.class_index = read_2_bytes(file);
      class_file.constant_pool[i].Fieldref.name_and_type_index = read_2_bytes(file);
      break;

    case CONSTANT_METHOD_REF:
      class_file.constant_pool[i].Methodref.class_index = read_2_bytes(file);
      class_file.constant_pool[i].Methodref.name_and_type_index = read_2_bytes(file);
      break;

    case CONSTANT_INTERFACE_METHOD_REF:
      class_file.constant_pool[i].InterfaceMethodref.class_index = read_2_bytes(file);
      class_file.constant_pool[i].InterfaceMethodref.name_and_type_index = read_2_bytes(file);
      break;

    case CONSTANT_STRING:
      class_file.constant_pool[i].String.string_index = read_2_bytes(file);
      break;

    case CONSTANT_INT:
      class_file.constant_pool[i].Integer.bytes = read_4_bytes(file);
      break;

    case CONSTANT_FLOAT:
      class_file.constant_pool[i].Float.bytes = read_4_bytes(file);
      break;

    case CONSTANT_LONG:
      class_file.constant_pool[i].Long.high_bytes = read_4_bytes(file);
      class_file.constant_pool[i].Long.low_bytes = read_4_bytes(file);
      i++;
      break;

    case CONSTANT_DOUBLE:
      class_file.constant_pool[i].Double.high_bytes = read_4_bytes(file);
      class_file.constant_pool[i].Double.low_bytes = read_4_bytes(file);
      i++;
      break;

    case CONSTANT_NAME_TYPE:
      class_file.constant_pool[i].NameAndType.name_index = read_2_bytes(file);
      class_file.constant_pool[i].NameAndType.descriptor_index = read_2_bytes(file);
      break;

    case CONSTANT_UTF8:
      // Talvez precise de '/0' no final e o +1 no size do malloc
      class_file.constant_pool[i].Utf8.length = read_2_bytes(file);
      class_file.constant_pool[i].Utf8.bytes = (u1*) malloc((class_file.constant_pool[i].Utf8.length + 1) * sizeof(u1));
      fread(class_file.constant_pool[i].Utf8.bytes, 1, class_file.constant_pool[i].Utf8.length, file);
      class_file.constant_pool[i].Utf8.bytes[class_file.constant_pool[i].Utf8.length] = '\0';
      break;
    }
  }
}

/**
 * @brief Lê o texto utf8 da constant pool
 * @param index
 * @param class_file
 * @return std::string
 */
std::string get_cp_info_utf8(Class_File class_file, u2 index){
  std::string utf8_text;

  switch (class_file.constant_pool[index].tag) {
    case CONSTANT_CLASS:
      utf8_text = get_cp_info_utf8(class_file, class_file.constant_pool[index].Class.class_name);                       
      break;

    case CONSTANT_FIELD_REF:
      index = class_file.constant_pool[index].Fieldref_Info.field_ref_class_ref; 
      utf8_text = get_cp_info_utf8(class_file, index);                                   
      utf8_text = get_cp_info_utf8(class_file, class_file.constant_pool[index].Fieldref.class_index);                                   
      utf8_text += "." + get_cp_info_utf8(class_file, class_file.constant_pool[index].Fieldref.name_and_type_index);                                   
      break;

    case CONSTANT_METHOD_REF:
      utf8_text = get_cp_info_utf8(class_file, class_file.constant_pool[index].Methodref.class_index);                                   
    case CONSTANT_DOUBLE:
    case CONSTANT_NAME_TYPE:
      index_aux = class_file.constant_pool[index].NameAndType_Info.name_type_index;            
      utf8_text = get_cp_info_utf8(class_file, index_aux);                                             
      index_aux = class_file.constant_pool[index].NameAndType_Info.name_type_descriptor_index; 
      break;
    case CONSTANT_UTF8:
      utf8_text = (char *)class_file.constant_pool[index].Utf8_Info.UTF8_bytes; 
      break;
      utf8_text += get_utf8_constant_pool(cp_info, cp_info[index].String.string_index);   
      break;

    case CONSTANT_NAME_TYPE:
      utf8_text += get_utf8_constant_pool(cp_info, cp_info[index].NameAndType.descriptor_index);
      break;

    case CONSTANT_UTF8:
      break;

    default: 
      return "";
  }
  return utf8_text;
}

/**
 * @brief Verifica se o this_class é igual ao nome do arquivo fonte. Se nao for, emite uma mensagem de erro
 * @param cp_info
 * @param index
 * @return std::string
 */
void get_cp_info_class_name(std::string filename, Class_File class_file) {
  std::string class_name = get_cp_info_utf8(class_file, class_file.this_class);
  class_name += ".class";

  if (DEBUG) std::cout << "This Class:           " << class_name << std::endl;

  std::size_t backslash_index = filename.find_last_of("/\\");
  std::string class_filename = filename.substr(backslash_index + 1);
  if (DEBUG)
    std::cout << "Source File Name:     " << class_filename << std::endl;

  if (class_filename != class_name) {
    printf("O nome do arquivo nao corresponde ao da classe!\n");
    exit(1);
  }
}