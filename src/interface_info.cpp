#include "file_reader.hpp"

void read_interface_info(FILE *file, Class_File_Format *class_file) {
  for (int i = 0; i < class_file->interfaces_count; i++)
    class_file->interfaces[i] = get_interface_info(file, class_file, class_file->interfaces[i]);
}

Interface_Info get_interface_info(FILE *file, Class_File_Format *class_file, Interface_Info interface_info) {
	interface_info.interface_table = read_2_bytes(file);
	return interface_info;
}