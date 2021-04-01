#ifndef __CP_INFO_H__
#define __CP_INFO_H__

#include "types.hpp"
#include "class_file.hpp"
#include <cstring>

struct Class_File;

struct Cp_Info {
  u2 tag;

  union {
    struct {
      u2 class_name; 
    } Class;    

    /* Field: represents a class or an interface */
    struct {
      u2 class_index;
      u2 name_and_type_index;
    } Fieldref; 

    /* Method: represents a class or an interface */
    struct {
      u2 class_index; 
      u2 name_and_type_index;
    } Methodref; 

    /* 
      NameAndType: represents a field or method, without indicating which class or interface type it belongs to
      name_index/descriptor_index items must be valid indexes into the pool table 
    */
    struct {
      u2 name_index;
      u2 descriptor_index;
    } NameAndType; 

    /* InterfaceMethod: represents constant objects of the type String) */
    struct {
      u2 class_index;
      u2 name_and_type_index;
    } InterfaceMethodref; 

    /* String: represents constant objects of the type String */
    struct {
      u2 string_index;
    } String; 

    /* Int: represents 4-byte numeric int constants */
    struct {
      u4 bytes;
    } Integer; 

    /* Float: represents 4-byte numeric float constants */
    struct {
      u4 bytes;
    } Float; 

    /* 
      Long: represents 8-byte numeric long constants
      Big-endian
      Occupies 2 indexes in pool table 
    */
    struct {
      u4 high_bytes;
      u4 low_bytes;
    } Long; 

    /* 
      Double: represents 8-byte numeric double constants
      Big-endian, IEEE-754
      Occupies 2 indexes in pool table 
    */
    struct {
      u4 high_bytes;
      u4 low_bytes;
    } Double; 

    /* 
      Utf8: represents a field or method
      Length tem gives the number of bytes in the bytes array
      Bytes array contains the bytes of the string
      Not allowed zero values or value between the interval 0xf0 to 0xff -> [240, 255] 
    */
    struct {
      u2 length;
      u1 *bytes;
    } Utf8; 

    struct {
      u1 reference_kind;
      u2 reference_index;
    } MethodHandle; 

    struct {
      u2 descriptor_index;
    } MethodType; 

    struct {
      u2 bootstrap_method_attr_index;
      u2 name_and_type_index;
    } InvokeDynamic; 
  };
};

void read_cp_info(FILE *file, Class_File* class_file);
void get_cp_info_class_name(std::string filename, Class_File* class_file);
std::string get_cp_info_utf8(Class_File class_file, u2 index);

#endif //__CP_INFO_H__