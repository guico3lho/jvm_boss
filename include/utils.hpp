/** 
 *  @file utils.hpp
 *  @brief Declaração de funções auxiliares
 */

#ifndef __UTILS__
#define __UTILS__

#include "class_file.hpp"

struct Class_File;
struct Attribute_Info;
struct Inner_Class_Attribute;

void print_command_error();

float float_bits_to_value(u4 float_bits);
u4 float_value_to_bits(float float_value);

double double_bits_to_value(u8 double_bits);

void freeClass(Class_File class_file);
void freeAttribute(Attribute_Info* attr, u4 size);
void freeInnerClass(Inner_Class_Attribute* inner, u4 size);

#endif