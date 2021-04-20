/** 
 *  @file utils.hpp
 *  @brief 
 */

#ifndef __UTILS__
#define __UTILS__

#include "class_file.hpp"

struct Class_File;
struct Attribute_Info;
struct Inner_Class_Attribute;

void print_command_error();

void freeClass(Class_File class_file);
void freeAttribute(Attribute_Info* attr, u4 size);
void freeInnerClass(Inner_Class_Attribute* inner, u4 size);

#endif