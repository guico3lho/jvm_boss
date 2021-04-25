/**
 * @file read_bytes.cpp
 * @brief Arquivo que contém as funções para ler bytes.
 */

#include "read_bytes.hpp"

/** 
 * @brief Lê 1 byte de um arquivo
 * @param *fp ponteiro para o arquivo que vai ser lido.
 * @return u1 os bytes lidos
 */
u1 read_1_byte(FILE* fp) {
  u1 bytes_read = getc(fp);
  return bytes_read;
}

/** 
 * @brief Lê 2 byte de um arquivo
 * @param *fp ponteiro para o arquivo que vai ser lido.
 * @return u2 os bytes lidos
 */
u2 read_2_bytes(FILE* fp) {
  u2 bytes_read = getc(fp);
  bytes_read = (bytes_read << 8) | (getc(fp));
  return bytes_read;
}

/** 
 * @brief Lê 4 byte de um arquivo
 * @param fp ponteiro para o arquivo que vai ser lido
 * @return u4 os bytes lidos
 */
u4 read_4_bytes(FILE* fp) {
  u4 bytes_read = getc(fp);
  bytes_read = (bytes_read << 8) | (getc(fp));
  bytes_read = (bytes_read << 8) | (getc(fp));
  bytes_read = (bytes_read << 8) | (getc(fp));
  return bytes_read;
}