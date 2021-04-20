/**
 *  @file interface_info.cpp
 *  @brief Arquivo com a função que lê as interfaces do arquivo e as armazena no class_file.
 */

#include "class_file.hpp"

void read_interface_info(FILE *file, Class_File *class_file) {
  for (int i = 0; i < class_file->interfaces_count; i++)
    class_file->interfaces[i].interface_table = read_2_bytes(file);
}
