/** 
 *  @file method_info.hpp
 *  @brief Estruturas e declarações de funções relacionadas a Method
 */

#ifndef __METHOD_INFO_H__
#define __METHOD_INFO_H__

#include "attribute_info.hpp"
#include "class_file.hpp"

struct Class_File;
struct Attribute_Info;

/** 
 *  @brief Method_Info - Estrutura que armazena o Method
 */
typedef struct Method_Info{
  u2 name_index;
  u2 descriptor_index;
	u2 access_flags;
  u2 attributes_count;
  
  Attribute_Info *attributes;
} Method_Info;

void read_method_info(FILE *file, Class_File *class_file);

Method_Info* find_main(Class_File class_file);
Method_Info *find_method(Class_File, std::string, std::string);

#endif
