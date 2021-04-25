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

struct Class_File;
struct Attribute_Info;
struct Inner_Class_Attribute;

// Define usada pelo dev para printar o nome da variável e seu valor
#define LOG(a)                                           \
    do                                                    \
    {                                                     \
        std::cout << #a ": " << (a) << std::endl; \
    } while (false)

// Define usado para printar algo pro usuário do sistema.
#define PRINT(a)                                           \
    do                                                    \
    {                                                     \
        std::cout  << (a) << std::endl; \
    } while (false)

void print_command_error();

void freeClass(Class_File class_file);
void freeAttribute(Attribute_Info* attr,u4 size);
void freeInner(Inner_Class_Attribute* inner,u4 size);

#endif 
