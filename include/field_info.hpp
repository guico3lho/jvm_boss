#ifndef __FIELD_INFO_H__
#define __FIELD_INFO_H__

#include "read_bytes.hpp"
#include "attribute_info.hpp"

typedef struct {
	u2  access_flag;      // CONSTANT_UTF8, field name
  u2  name_index;       // CONSTANT_UTF8, field valid descriptor
  u2  descriptor_index; // number of field attributes

  //* JVM implementation should ignore in silence each unrecognized attribute 
  u2  atributes_count;
  Attribute_Info  *attributes;

} Field_Info;


#endif
