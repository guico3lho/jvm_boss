#include "read_bytes.hpp"

u1 read_1_byte(FILE* fp) {
  uint8_t bytes_read = getc(fp);
  return bytes_read;
}

u2 read_2_bytes(FILE* fp) {
  uint16_t bytes_read = getc(fp);
  bytes_read = (bytes_read << 8) | (getc(fp));
  return bytes_read;
}

u4 read_4_bytes(FILE* fp) {
  uint32_t bytes_read = getc(fp);
  bytes_read = (bytes_read << 8) | (getc(fp));
  bytes_read = (bytes_read << 8) | (getc(fp));
  bytes_read = (bytes_read << 8) | (getc(fp));
  return bytes_read;
}
