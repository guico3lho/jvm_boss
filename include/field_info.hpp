#ifndef __FIELD_INFO_H__
#define __FIELD_INFO_H__

#include "attribute_info.hpp"
#include "file_reader.hpp"

struct Class_File_Format;
struct Attribute_Info;

typedef struct Field_Info{
	u2  access_flag;      // CONSTANT_UTF8, field name
  u2  name_index;       // CONSTANT_UTF8, field valid descriptor
  u2  descriptor_index; // number of field attributes

  //* JVM implementation should ignore in silence each unrecognized attribute 
  u2  atributes_count;
  Attribute_Info  *attributes;

} Field_Info;

/* FIELD_INFO */
void read_field_info(FILE *file, Class_File_Format *class_file);

#endif
