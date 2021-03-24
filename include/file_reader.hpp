#ifndef __FILE_READER_H__
#define __FILE_READER_H__

#include "read_bytes.hpp"
#include "cp_info.hpp"
#include "interface_info.hpp"
#include "field_info.hpp"
#include "method_info.hpp"
#include "attribute_info.hpp"

struct Cp_Info;
struct Interface_Info;
struct Field_Info;
struct Attribute_Info;
struct Method_Info;
struct Inner_Class_Attribute;


typedef struct Class_File{
  u4 magic_number;

  u2 minor_version;   
  u2 major_version;

  u2 constant_pool_count;   
  Cp_Info *constant_pool = nullptr;

  u2 access_flags;
  u2 this_class;
  u2 super_class;

  u2 interfaces_count;   
  Interface_Info *interfaces = nullptr;

  u2 fields_count;   
  Field_Info *fields = nullptr;

  u2 methods_count;
  Method_Info *methods = nullptr;

  u2 attributes_count;   
  Attribute_Info *attributes = nullptr;
} Class_File;

Class_File read_class_file(std::string filename);

void freeClass(Class_File class_file);
void freeAttribute(Attribute_Info* attr,u4 size);
void freeInner(Inner_Class_Attribute* inner,u4 size);


#endif 
