#include "frame.hpp"
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
        Class_File info_class = get_class_info_and_load_not_exists(class_realname);

        new_type->class_loader->class_file = info_class;
        new_type->class_loader->class_name = &class_realname;

        load_class_var(new_type->class_loader);
      }
      break;
  }
  return new_type;
}