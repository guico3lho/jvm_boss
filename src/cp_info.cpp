#include "file_reader.hpp"

void read_cp_info(FILE *file, Class_File_Format *class_file) {
  // Constant Pool Table
  // All indexes are 16-bit - 2 bytes
  // Index 1 refers to first constant in the table (index 0 is invalid)
  // The number of constants in the constant pool table is not actually the same as the constant pool count
  for(int i = 0; i < class_file->constant_pool_count - 1; i++) {
    class_file->constant_pool[i].tag = read_1_byte(file);  

    switch (class_file->constant_pool[i].tag) {
      case CONSTANT_CLASS:
        class_file->constant_pool[i].class_name = read_2_bytes(file);
        break;
      case CONSTANT_FIELD_REF:
        class_file->constant_pool[i].field_ref_class_ref = read_2_bytes(file);
        class_file->constant_pool[i].field_ref_name_type_descriptor = read_2_bytes(file);
        break;
      case CONSTANT_METHOD_REF:
        class_file->constant_pool[i].method_ref_index = read_2_bytes(file);
        class_file->constant_pool[i].method_ref_name_and_type = read_2_bytes(file);
        break;
      case CONSTANT_INTERFACE_METHOD_REF:
        class_file->constant_pool[i].interface_method_ref_index = read_2_bytes(file);
        class_file->constant_pool[i].interface_method_ref_name_type = read_2_bytes(file);
        break;
      case CONSTANT_STRING:
        class_file->constant_pool[i].string_bytes = read_2_bytes(file);
        break;
      case CONSTANT_INT:
        class_file->constant_pool[i].int_bytes = read_4_bytes(file);
        break;
      case CONSTANT_FLOAT:
        class_file->constant_pool[i].float_bytes = read_4_bytes(file);
        break;
      case CONSTANT_LONG:
        class_file->constant_pool[i].long_high_bytes = read_4_bytes(file);
        class_file->constant_pool[i].long_low_bytes = read_4_bytes(file);
        i++;
        break;
      case CONSTANT_DOUBLE:
        class_file->constant_pool[i].double_high_bytes = read_4_bytes(file);
        class_file->constant_pool[i].double_low_bytes = read_4_bytes(file);
        i++;
        break;
      case CONSTANT_NAME_TYPE:
        class_file->constant_pool[i].name_type_index = read_2_bytes(file);
        class_file->constant_pool[i].name_type_descriptor_index = read_2_bytes(file);
        break;
      case CONSTANT_UTF8:
          class_file->constant_pool[i].UTF8_size = read_2_bytes(file);
          class_file->constant_pool[i].UTF8_bytes = (u1*) calloc((class_file->constant_pool[i].UTF8_size) + 1, sizeof(u1));
          fread(class_file->constant_pool[i].UTF8_bytes, 1, class_file->constant_pool[i].UTF8_size, file);
          class_file->constant_pool[i].UTF8_bytes[class_file->constant_pool[i].UTF8_size] = '\0';
        break;
    }
  }
}

std::string get_cp_info_utf8(Cp_Info *cp_info, u2 pos_info) {
  std::string utf8_const;
  u2 tag = cp_info[pos_info].tag;

  switch (tag) {
    case CONSTANT_UTF8: // caso tag seja 1
      // representa valores strings constantes, inclusive unicode
      // UTF8_size indica o número de bytes no array bytes
      // UTF8_bytes contêm os bytes da string
      // @TODO checar se nenhum byte tem valor 0 ou está no intervalo
      //  0xf0 ou 0xff, i.e. [240, 255]
      utf8_const = (char*) cp_info[pos_info].UTF8_bytes;
      break;
    case CONSTANT_CLASS:
      utf8_const = get_cp_info_utf8(cp_info, cp_info[pos_info].class_name - 1);
      break;
    case CONSTANT_FIELD_REF:
      utf8_const = get_cp_info_utf8(cp_info, cp_info[pos_info].field_ref_class_ref - 1);
      utf8_const += get_cp_info_utf8(cp_info, cp_info[pos_info].field_ref_name_type_descriptor - 1);
      break;
    // caso tag seja 12
    case CONSTANT_NAME_TYPE:
      // representa um nome simples de field ou método ou ainda o nome do método especial <init>
      utf8_const = get_cp_info_utf8(cp_info, cp_info[pos_info].name_type_index - 1);
      // representa um descritor válido de field ou de método
      utf8_const += get_cp_info_utf8(cp_info, cp_info[pos_info].name_type_descriptor_index - 1);
      break;
    case CONSTANT_METHOD_REF:
      utf8_const = get_cp_info_utf8(cp_info, cp_info[pos_info].method_ref_index - 1);
      utf8_const += get_cp_info_utf8(cp_info, cp_info[pos_info].method_ref_name_and_type - 1);
      break;
    case CONSTANT_INTERFACE_METHOD_REF:
      utf8_const = get_cp_info_utf8(cp_info, cp_info[pos_info].interface_method_ref_index - 1);
      utf8_const += get_cp_info_utf8(cp_info, cp_info[pos_info].interface_method_ref_name_type - 1);
      break;
    case CONSTANT_STRING:
      utf8_const += get_cp_info_utf8(cp_info, cp_info[pos_info].string_bytes - 1);
      break;
    default:
      return "";
  }

  return utf8_const;
}

//* Pega nome da classe no CP e converte pra String
void get_cp_info_class_name(std::string filename, Class_File_Format *class_file) {
  std::string class_name = get_cp_info_utf8(class_file->constant_pool, class_file->this_class - 1);
  class_name += ".class";
  // if (DEBUG) std::cout << "CLASS NAME:           " << class_name << std::endl;

  std::size_t backslash_index = filename.find_last_of("/\\");
  std::string class_filename = filename.substr(backslash_index + 1);
  // if (DEBUG) std::cout << "Filename:             " << class_filename << std::endl;

  if (class_filename != class_name) {
    printf("O nome do arquivo nao corresponde ao da classe!\n");
    exit(1);
  }
}