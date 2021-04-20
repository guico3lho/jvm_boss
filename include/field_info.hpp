/** 
 *  @file field_info.hpp
 *  @brief Estruturas e declarações de funções relacionadas a Field
*/

#ifndef __FIELD_INFO_H__
#define __FIELD_INFO_H__

#include "attribute_info.hpp"
#include "class_file.hpp"

struct Class_File;
struct Attribute_Info;

/**
 * @brief Field_Info - estrutura de dados que armazena os Fields
 */
typedef struct Field_Info{
	u2  access_flags;     //  mask of flags to denote access permission
  u2  name_index;       // CONSTANT_UTF8, field name
  u2  descriptor_index; // CONSTANT_UTF8, field valid descriptor
  u2  atributes_count;  // number of field attributes

  Attribute_Info  *attributes;
} Field_Info;

void read_field_info(FILE *file, Class_File *class_file);

#endif
