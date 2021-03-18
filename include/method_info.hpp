#ifndef __METHOD_INFO_H__
#define __METHOD_INFO_H__

#include "attribute_info.hpp"
#include "file_reader.hpp"

struct Class_File_Format;
struct Attribute_Info;


typedef struct Method_Info{
	u2 access_flags;
  u2 name_index;
  u2 descriptor_index;
  u2 attributes_count;
  
  Attribute_Info *attributes;
} Method_Info;

void read_method_info(FILE *file, Class_File_Format *class_file);

#endif