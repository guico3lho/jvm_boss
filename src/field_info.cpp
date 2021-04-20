/**
 * @file field_info.cpp
 * @brief 
*/

#include "field_info.hpp"

void read_field_info(FILE *file, Class_File *class_file) {

  for (int i = 0; i < class_file->fields_count; i++) {
    class_file->fields[i].access_flags = read_2_bytes(file);
    class_file->fields[i].name_index = read_2_bytes(file);
    class_file->fields[i].descriptor_index = read_2_bytes(file);

    class_file->fields[i].atributes_count = read_2_bytes(file);
    class_file->fields[i].attributes = (Attribute_Info*) malloc((class_file->fields[i].atributes_count) * sizeof(Attribute_Info));

    for (int j = 0;  j < class_file->fields[i].atributes_count; j++) {
      class_file->fields[i].attributes[j] = get_attribute_info(file, class_file);
    }
  }
}