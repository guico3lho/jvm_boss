#ifndef __CP_INFO_H__
#define __CP_INFO_H__

#include "read_bytes.hpp"

typedef struct {
  u1 tag;

  // not allowed zero values or value between the interval 0xf0 to 0xff,
  // that means, [240, 255]
  u2 UTF8_size;
  u1 *UTF8_bytes;

  u4 int_bytes;
  u4 float_bytes;

  // Long - integer constant of 8 bytes (big-endian), occupies 2 indexes in constant_pool table
  u4 long_high_bytes;
  u4 long_low_bytes;

  // Double - float constant of 8 bytes (big-endian, IEEE-754), occupies 2 indexes in constant_pool table
  u4 double_high_bytes;
  u4 double_low_bytes;

  u2 class_name; // big-endian

  u2 string_bytes;

  u2 field_ref_class_ref;
  u2 field_ref_name_type_descriptor;

  u2 method_ref_index;
  u2 method_ref_name_and_type;

  u2 interface_method_ref_index;
  u2 interface_method_ref_name_type;

  u2 name_type_index;
  u2 name_type_descriptor_index;

} Cp_Info;

std::string get_utf8_constant_pool(Cp_Info *cp_info, u2 pos_info);

#endif