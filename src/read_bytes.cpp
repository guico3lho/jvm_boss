/**
 * @file read_bytes.cpp
 * @brief Arquivo que contém as funções para ler bytes.
 */

#include "read_bytes.hpp"

u1 read_1_byte(FILE* fp) {
  u1 bytes_read = getc(fp);
  return bytes_read;
}

u2 read_2_bytes(FILE* fp) {
  u2 bytes_read = getc(fp);
  bytes_read = (bytes_read << 8) | (getc(fp));
  return bytes_read;
}

u4 read_4_bytes(FILE* fp) {
  u4 bytes_read = getc(fp);
  bytes_read = (bytes_read << 8) | (getc(fp));
  bytes_read = (bytes_read << 8) | (getc(fp));
  bytes_read = (bytes_read << 8) | (getc(fp));
  return bytes_read;
}
