#include "method_info.hpp"

void read_method_info(FILE *file, Class_File_Format *class_file) {

  for (int i = 0; i < class_file->methods_count; i++) {
    if (PRINT) printf("\nMethod: %d\n", i);

    class_file->methods[i].access_flags = read_2_bytes(file);
    class_file->methods[i].name_index = read_2_bytes(file);
    class_file->methods[i].descriptor_index = read_2_bytes(file);

    class_file->methods[i].attributes_count = read_2_bytes(file);
    class_file->methods[i].attributes = (Attribute_Info*) malloc(class_file->methods[i].attributes_count * sizeof(Attribute_Info));
    if (PRINT) std::cout << "attributes_count: " << class_file->methods[i].attributes_count << std::endl;

    for (int j = 0; j < class_file->methods[i].attributes_count; j++) {
      if (PRINT) std::cout << "Reading Attribute " << j << std::endl;
      class_file->methods[i].attributes[j] = get_attribute_info(file, class_file);
    }
  }
}
