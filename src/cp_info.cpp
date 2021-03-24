#include "cp_info.hpp"


void read_cp_info(Class_File class_file, FILE *file) {
  int count = class_file.constant_pool_count;
  for (int i = 1; i < count; i++) {
    // tenho o constant pool count, quero ler de cada um, pra isso preciso ler o próximo?
    u2 tag = read_1_byte(file);
    class_file.constant_pool[i].tag = tag;

    switch (tag) {
    case CONSTANT_CLASS:
      class_file.constant_pool[i].Class_Info.class_name = read_2_bytes(file);
      break;
    case CONSTANT_FIELD_REF:
      class_file.constant_pool[i].Fieldref_Info.field_ref_class_ref = read_2_bytes(file);
      class_file.constant_pool[i].Fieldref_Info.field_ref_name_type_descriptor = read_2_bytes(file);
      break;
    case CONSTANT_METHOD_REF:
      class_file.constant_pool[i].Methodref_Info.method_ref_index = read_2_bytes(file);
      class_file.constant_pool[i].Methodref_Info.method_ref_name_and_type = read_2_bytes(file);
      break;
    case CONSTANT_INTERFACE_METHOD_REF:
      class_file.constant_pool[i].InterfaceMethodref_Info.interface_method_ref_index = read_2_bytes(file);
      class_file.constant_pool[i].InterfaceMethodref_Info.interface_method_ref_name_type = read_2_bytes(file);
      break;
    case CONSTANT_STRING:
      class_file.constant_pool[i].String_Info.string_index = read_2_bytes(file);
      break;
    case CONSTANT_INT:
      class_file.constant_pool[i].Integer_Info.int_bytes = read_4_bytes(file);
      break;
    case CONSTANT_FLOAT:
      class_file.constant_pool[i].Float_Info.float_bytes = read_4_bytes(file);
      break;
    case CONSTANT_LONG:
      class_file.constant_pool[i].Long_Info.long_high_bytes = read_4_bytes(file);
      class_file.constant_pool[i].Long_Info.long_low_bytes = read_4_bytes(file);
      i++;
      break;
    case CONSTANT_DOUBLE:
      class_file.constant_pool[i].Double_Info.double_high_bytes = read_4_bytes(file);
      class_file.constant_pool[i].Double_Info.double_low_bytes = read_4_bytes(file);
      i++;
      break;
    case CONSTANT_NAME_TYPE:
      class_file.constant_pool[i].NameAndType_Info.name_type_index = read_2_bytes(file);
      class_file.constant_pool[i].NameAndType_Info.name_type_descriptor_index = read_2_bytes(file);
      break;
    case CONSTANT_UTF8:
      // Talvez precise de '/0' no final e o +1 no size do malloc
      class_file.constant_pool[i].Utf8_Info.UTF8_size = read_2_bytes(file);
      class_file.constant_pool[i].Utf8_Info.UTF8_bytes = (u1 *)malloc((class_file.constant_pool[i].Utf8_Info.UTF8_size + 1) * sizeof(u1));
      fread(class_file.constant_pool[i].Utf8_Info.UTF8_bytes, 1, class_file.constant_pool[i].Utf8_Info.UTF8_size, file);
      class_file.constant_pool[i].Utf8_Info.UTF8_bytes[class_file.constant_pool[i].Utf8_Info.UTF8_size] = '\0';
      break;
    }
  }
}

std::string get_cp_info_utf8(Class_File class_file, u2 index){
  std::string utf8_text;
  u2 index_aux;
  switch (class_file.constant_pool[index].tag) {
    case CONSTANT_CLASS:
      index = class_file.constant_pool[index].Class_Info.class_name; 
      utf8_text = get_cp_info_utf8(class_file, index);                       
      break;
    case CONSTANT_FIELD_REF:
      index = class_file.constant_pool[index].Fieldref_Info.field_ref_class_ref; 
      utf8_text = get_cp_info_utf8(class_file, index);                                   
      break;
    case CONSTANT_METHOD_REF:
      break;
    case CONSTANT_INTERFACE_METHOD_REF:
      break;
    case CONSTANT_STRING:
      index = class_file.constant_pool[index].String_Info.string_index; 
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
      index_aux = class_file.constant_pool[index].NameAndType_Info.name_type_index;            
      utf8_text = get_cp_info_utf8(class_file, index_aux);                                             
      index_aux = class_file.constant_pool[index].NameAndType_Info.name_type_descriptor_index; 
      utf8_text += get_cp_info_utf8(class_file, index_aux);
      break;
    case CONSTANT_UTF8:
      utf8_text = (char *)class_file.constant_pool[index].Utf8_Info.UTF8_bytes; 
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