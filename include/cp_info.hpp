#ifndef __CP_INFO_H__
#define __CP_INFO_H__

#include "types.hpp"
#include "class_file.hpp"
#include "utils.hpp"
#include <cstring>

struct Class_File;

typedef struct Cp_Info{
  u1 tag;

  u2 class_name; // big-endian

  u2 field_ref_class_index;
  u2 field_ref_name_type_index;

    /* Method: represents a class or an interface */
    struct {
      u2 method_ref_index; 
      u2 method_ref_name_and_type;
    } Methodref_Info; 

  u2 string_bytes;
  u4 int_bytes;
  u4 float_bytes;

  // Long - integer constant of 8 bytes (big-endian), occupies 2 indexes in constant_pool table
  u4 long_high_bytes;
  u4 long_low_bytes;

  // Double - float constant of 8 bytes (big-endian, IEEE-754), occupies 2 indexes in constant_pool table
  u4 double_high_bytes;
  u4 double_low_bytes;

  u2 name_type_index;
  u2 name_type_descriptor_index;

  //* Not allowed zero values or value between the interval 0xf0 to 0xff -> [240, 255]
  u2 UTF8_size;
  u1 *UTF8_bytes;

} Cp_Info;

void read_cp_info(FILE *file, Class_File *class_file);
std::string get_cp_info_utf8(Cp_Info *cp_info, u2 index);
void get_cp_info_class_name(std::string filename, Class_File *class_file);

#endif