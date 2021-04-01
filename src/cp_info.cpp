#include "cp_info.hpp"

void read_cp_info(FILE *file, Class_File *class_file) {
  // Constant Pool Table
  // All indexes are 16 bits = 2 bytes
  // Number of constants in the constant pool table is constant_pool_count - 1
  for(int i = 1; i < class_file->constant_pool_count; i++) {
    class_file->constant_pool[i].tag = read_1_byte(file);  

    switch (class_file->constant_pool[i].tag) {
      case CONSTANT_CLASS:
        class_file->constant_pool[i].Class.class_name = read_2_bytes(file);
        break;
      case CONSTANT_FIELD_REF:
        class_file->constant_pool[i].Fieldref.class_index = read_2_bytes(file);
        class_file->constant_pool[i].Fieldref.name_and_type_index = read_2_bytes(file);
        break;
      case CONSTANT_METHOD_REF:
        class_file->constant_pool[i].Methodref.class_index = read_2_bytes(file);
        class_file->constant_pool[i].Methodref.name_and_type_index = read_2_bytes(file);
        break;
      case CONSTANT_INTERFACE_METHOD_REF:
        class_file->constant_pool[i].InterfaceMethodref.class_index = read_2_bytes(file);
        class_file->constant_pool[i].InterfaceMethodref.name_and_type_index = read_2_bytes(file);
        break;
      case CONSTANT_STRING:
        class_file->constant_pool[i].String.string_index = read_2_bytes(file);
        break;
      case CONSTANT_INT:
        class_file->constant_pool[i].Integer.bytes = read_4_bytes(file);
        break;
      case CONSTANT_FLOAT:
        class_file->constant_pool[i].Float.bytes = read_4_bytes(file);
        break;
      case CONSTANT_LONG:
        class_file->constant_pool[i].Long.high_bytes = read_4_bytes(file);
        class_file->constant_pool[i].Long.low_bytes = read_4_bytes(file);
        i++;
        break;
      case CONSTANT_DOUBLE:
        class_file->constant_pool[i].Double.high_bytes = read_4_bytes(file);
        class_file->constant_pool[i].Double.low_bytes = read_4_bytes(file);
        i++;
        break;
      case CONSTANT_NAME_TYPE:
        class_file->constant_pool[i].NameAndType.name_index = read_2_bytes(file);
        class_file->constant_pool[i].NameAndType.descriptor_index = read_2_bytes(file);
        break;
      case CONSTANT_UTF8:
        class_file->constant_pool[i].Utf8.length = read_2_bytes(file);
        class_file->constant_pool[i].Utf8.bytes = (u1*) calloc((class_file->constant_pool[i].Utf8.length) + 1, sizeof(u1));
        fread(class_file->constant_pool[i].Utf8.bytes, 1, class_file->constant_pool[i].Utf8.length, file);
        class_file->constant_pool[i].Utf8.bytes[class_file->constant_pool[i].Utf8.length] = '\0';
        break;
    }
  }
}

std::string get_cp_info_utf8(Class_File class_file, u2 index){
  std::string utf8_text;
  u2 index_aux;
  switch (class_file.constant_pool[index].tag) {
    case CONSTANT_CLASS:
      index = class_file.constant_pool[index].Class.class_name; 
      utf8_text = get_cp_info_utf8(class_file, index);                       
      break;
    case CONSTANT_FIELD_REF:
      index = class_file.constant_pool[index].Fieldref.class_index; 
      utf8_text = get_cp_info_utf8(class_file, index);                                   
      break;
    case CONSTANT_METHOD_REF:
      break;
    case CONSTANT_INTERFACE_METHOD_REF:
      break;
    case CONSTANT_STRING:
      index = class_file.constant_pool[index].String.string_index; 
      utf8_text = get_cp_info_utf8(class_file, index);   
      break;
    case CONSTANT_INT:
      break;
    case CONSTANT_FLOAT:
      break;
    case CONSTANT_LONG:
      break;
    case CONSTANT_DOUBLE:
      break;
    case CONSTANT_NAME_TYPE:
      index_aux = class_file.constant_pool[index].NameAndType.name_index;            
      utf8_text = get_cp_info_utf8(class_file, index_aux);                                             
      index_aux = class_file.constant_pool[index].NameAndType.descriptor_index; 
      utf8_text += get_cp_info_utf8(class_file, index_aux);
      break;
    case CONSTANT_UTF8:
      utf8_text = (char *)class_file.constant_pool[index].Utf8.bytes; 
      break;
  }
  return utf8_text;
}

// * Verifica se o this_class é igual ao nome do arquivo fonte
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