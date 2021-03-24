#ifndef __CP_INFO_H__
#define __CP_INFO_H__

#include "types.hpp"
#include "file_reader.hpp"
#include <string.h>
#include "functions.hpp"

struct Class_File;
 struct Cp_Info
{
  u2 tag;

  union
  {
    struct
    {
      u2 class_name; /* big-endian */
    } Class_Info;    // 7

    /* Field: represents a class or an interface */
    struct
    {
      u2 field_ref_class_ref;
      u2 field_ref_name_type_descriptor;
    } Fieldref_Info; // 9

    /* Method: represents a class or an interface */
    struct
    {
      u2 method_ref_index; //6

      u2 method_ref_name_and_type;
    } Methodref_Info; // 10

    /* InterfaceMethod: represents constant objects of the type String) */
    struct
    {
      u2 interface_method_ref_index;
      u2 interface_method_ref_name_type;
    } InterfaceMethodref_Info; //11

    /* String: represents constant objects of the type String */
    struct
    {
      u2 string_bytes;
    } String_Info; // 8

    /* Int: represents 4-byte numeric int constants */
    struct
    {
      u4 int_bytes;
    } Integer_Info; // 3

    /* Float: represents 4-byte numeric float constants */
    struct
    {
      u4 float_bytes;
    } Float_Info; // 4

    /* Long: represents 8-byte numeric long constants
            Big-endian
            Occupies 2 indexes in pool table */
    struct
    {
      u4 long_high_bytes;
      u4 long_low_bytes;
    } Long_Info; // 5

    /* Double: represents 8-byte numeric double constants
            Big-endian, IEEE-754
            Occupies 2 indexes in pool table */
    struct
    {
      u4 double_high_bytes;
      u4 double_low_bytes;
    } Double_Info; // 6

    /* NameAndType: represents a field or method, without indicating which class or interface type it belongs to
            Name_type_index/name_type_descriptor_index items must be valid indexes into the pool table */
    struct
    {
      u2 name_type_index;
      u2 name_type_descriptor_index;
    } NameAndType_Info; // 12

    /* Utf8: represents a field or method
            Length tem gives the number of bytes in the bytes array
            Bytes array contains the bytes of the string
            Not allowed zero values or value between the interval 0xf0 to 0xff -> [240, 255] */
    struct
    {
      u2 UTF8_size;
      u1 *UTF8_bytes;
    } Utf8_Info; //1

    /* MethodHandle */
    struct
    {
      u1 method_handle_reference_kind;
      u2 method_handle_reference_index;
    } MethodHandle_Info; // 15

    /* MethodType */
    struct
    {
      u2 method_type_descriptor_index;
    } MethodType_Info; // 16

    /* InvokeDynamic */
    struct
    {
      u2 invoke_dynamic_bootstrap_method_attr_index;
      u2 invoke_dynamic_name_type_index;
    } InvokeDynamic_Info; // 18
  };
  //
};

void cp_info_reader(Class_File class_file, FILE *file);
void cp_info_printer(Class_File class_file);
void get_cp_info_class_name(std::string filename, Class_File class_file);
std::string get_utf8(Class_File class_file, u2 index);
// std::string get_cp_info_utf8(Cp_Info *cp_info, int ref_idx);
#endif //__CP_INFO_H__
