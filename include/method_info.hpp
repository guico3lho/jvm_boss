#ifndef __METHOD_INFO_H__
#define __METHOD_INFO_H__

#include "read_bytes.hpp"
#include "attribute_info.hpp"

typedef struct {
	u2 access_flags;
  u2 name_index;
  u2 descriptor_index;
  u2 attributes_count;
  
  Attribute_Info *attributes;
} Method_Info;

#endif
