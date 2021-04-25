/** 
 *  @file cp_info.hpp
 *  @brief Estruturas e declarações de funções relacionadas a Constant Pool
 */

#ifndef __CP_INFO_H__
#define __CP_INFO_H__

#include "types.hpp"
#include "utils.hpp"
#include "class_file.hpp"
#include <cstring>

struct Class_File;

struct Cp_Info {
  u2 tag;
struct Cp_Info {
  u2 tag;

  union {

    /* Class: represents id of class_name on constant_pool*/
    struct {
      u2 class_name; 
    } Class;    // tag = 7

    /* Field: represents a class or an interface */
    struct {
      u2 class_index;
      u2 name_and_type_index;
    } Fieldref; // tag = 9

    /* Method: represents a class or an interface */
    struct {
      u2 class_index; 
      u2 name_and_type_index;
    } Methodref; // tag = 10

    /* 
      NameAndType: represents a field or method, without indicating which class or interface type it belongs to
      name_index/descriptor_index items must be valid indexes into the pool table 
    */
    struct {
      u2 name_index;
      u2 descriptor_index;
    } NameAndType; // tag = 12

    /* InterfaceMethod: represents constant objects of the type String) */
    struct {
      u2 class_index;
      u2 name_and_type_index;
    } InterfaceMethodref; // tag = 11

    /* String: represents constant objects of the type String */
    struct {
      u2 string_index;
    } String; // tag = 8

    /* Int: represents 4-byte numeric int constants */
    struct {
      u4 bytes;
    } Integer; // tag = 3

    /* Float: represents 4-byte numeric float constants */
    struct {
      u4 bytes;
    } Float; // tag = 4

    /* 
      Long: represents 8-byte numeric long constants
      Big-endian
      Occupies 2 indexes in pool table 
    */
    struct {
      u4 high_bytes;
      u4 low_bytes;
    } Long; // tag = 5

    /* 
      Double: represents 8-byte numeric double constants
      Big-endian, IEEE-754
      Occupies 2 indexes in pool table 
    */
    struct {
      u4 high_bytes;
      u4 low_bytes;
    } Double; // tag = 6

    /** 
     * @brief struct Utf8: represents a field or method Length tem gives the number of bytes 
     * in the bytes array Bytes array contains the bytes of the string 
     * Not allowed zero values or value between the interval 0xf0 to 0xff -> [240, 255] 
     *
     */
    struct {
      u2 length;
      u1 *bytes;
    } Utf8; // tag = 1

    struct {
      u1 reference_kind;
      u2 reference_index;
    } MethodHandle; // tag = 15

    struct {
      u2 descriptor_index;
    } MethodType; // tag = 16

    struct {
      u2 bootstrap_method_attr_index;
      u2 name_and_type_index;
    } InvokeDynamic; // tag = 18
  };
};

/**
 * @brief 
 * 
 * @param file 
 * @param class_file 
 */
void read_cp_info(FILE *file, Class_File class_file);

/**
 * @brief Checa se nome da classe é igual ao do arquivo
 * 
 * @param filename 
 * @param class_file 
 */
void get_cp_info_class_name(std::string filename, Class_File class_file);

/**
 * @brief retorna string de caracteres no formato UTF-8 a partir de um indice do constant pool
 * 
 * @param class_file 
 * @param index 
 * @return std::string 
 */
std::string get_cp_info_utf8(Class_File class_file, u2 index);

std::string get_utf8_constant_pool(Cp_Info* cp_info, u2 index);

#endif //__CP_INFO_H__
