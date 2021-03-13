#ifndef __FIELD_INFO_H__
#define __FIELD_INFO_H__

#include "read_bytes.hpp"
#include "attribute_info.hpp"

typedef struct {

	u2  access_flag; // CONSTANT_UTf8, field name
  u2  name_index; // CONSTANT_UTf8, field valid descriptor
  u2  descriptor_index; // number of field attributes

  // JVM implementation should ignore in silence each attribute unrecognized
  u2  atributes_count;
  Attribute_Info  *attributes;

} Field_Info;


#endif
