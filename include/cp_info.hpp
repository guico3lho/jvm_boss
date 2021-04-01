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
    } Class_Info;    

    /* Field: represents a class or an interface */
    struct {
      u2 field_ref_class_ref;
      u2 field_ref_name_type_descriptor;
    } Fieldref_Info; 

    /* Method: represents a class or an interface */
    struct {
      u2 method_ref_index; 

      u2 method_ref_name_and_type;
    } Methodref_Info; 

    /* InterfaceMethod: represents constant objects of the type String) */
    struct {
      u2 interface_method_ref_index;
      u2 interface_method_ref_name_type;
    } InterfaceMethodref_Info; 

    /* String: represents constant objects of the type String */
    struct {
      u2 string_index;
    } String_Info; 

    /* Int: represents 4-byte numeric int constants */
    struct {
        u4 int_bytes;
    } Integer_Info; 

    /* Float: represents 4-byte numeric float constants */
    struct {
      u4 float_bytes;
    } Float_Info; 

    /* 
      Long: represents 8-byte numeric long constants
      Big-endian
      Occupies 2 indexes in pool table 
    */
    struct {
      u4 long_high_bytes;
      u4 long_low_bytes;
    } Long_Info; 

    /* 
      Double: represents 8-byte numeric double constants
      Big-endian, IEEE-754
      Occupies 2 indexes in pool table 
    */
    struct {
        u4 double_high_bytes;
        u4 double_low_bytes;
    } Double_Info; 

    /* 
      NameAndType: represents a field or method, without indicating which class or interface type it belongs to
      Name_type_index/name_type_descriptor_index items must be valid indexes into the pool table 
    */
    struct {
        u2 name_type_index;
        u2 name_type_descriptor_index;
    } NameAndType_Info; 

    /* 
      Utf8: represents a field or method
      Length tem gives the number of bytes in the bytes array
      Bytes array contains the bytes of the string
      Not allowed zero values or value between the interval 0xf0 to 0xff -> [240, 255] 
    */
    struct {
      u2 UTF8_size;
      u1 *UTF8_bytes;
    } Utf8_Info; 

    /* MethodHandle */
    struct {
      u1 method_handle_reference_kind;
      u2 method_handle_reference_index;
    } MethodHandle_Info; 

    /* MethodType */
    struct {
      u2 method_type_descriptor_index;
    } MethodType_Info; 

    /* InvokeDynamic */
    struct {
      u2 invoke_dynamic_bootstrap_method_attr_index;
      u2 invoke_dynamic_name_type_index;
    } InvokeDynamic_Info; 
  };
};

void read_cp_info(Class_File class_file, FILE *file);
void get_cp_info_class_name(std::string filename, Class_File class_file);
std::string get_cp_info_utf8(Class_File class_file, u2 index);

#endif //__CP_INFO_H__
