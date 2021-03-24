#include "file_reader.hpp"

void read_interface_info(FILE *file, Class_File *class_file) {
  for (int i = 0; i < class_file->interfaces_count; i++)
    class_file->interfaces[i].interface_table = read_2_bytes(file);
}
