#ifndef __ATTRIBUTE_INFO_H__
#define __ATTRIBUTE_INFO_H__

#include "read_bytes.hpp"

typedef struct {

} Code_Attribute;

typedef struct {

  

  u2 attribute_name_index; // valid unsigned 16-bit index into the constant pool of the class
  u4 attribute_length;


} Attribute_Info;


#endif
