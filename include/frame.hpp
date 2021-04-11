#ifndef __FRAME_H__
#define __FRAME_H__

#include <vector>

struct Class_Loader;
struct Array_Type;

typedef struct Operand {
  u1 tag; // CONSTANT_Integer, CONSTANT_Float, etc
  union{
    u4 type_bool;
    u4 type_byte;
    u4 type_char;
    u4 type_short;
    u4 type_int;
    u4 type_float;
    u8 type_long;
    u8 type_double;
    std::string* type_string;
    Class_Loader *class_loader;
    Array_Type *array_type;
  };
} Operand;

typedef struct Array_Type{  
  std::vector<Operand*> *array;
} Array_Type;

#endif