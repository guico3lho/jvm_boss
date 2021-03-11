#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdint.h>

#define CONSTANT_EmptySpace            0
#define CONSTANT_UTF8                  1
#define CONSTANT_INT                   3
#define CONSTANT_FLOAT                 4
#define CONSTANT_LONG                  5
#define CONSTANT_DOUBLE                6
#define CONSTANT_CLASS                 7
#define CONSTANT_STRING                8
#define CONSTANT_FIELD_REF             9
#define CONSTANT_METHOD_REF            10
#define CONSTANT_INTERFACE_METHOD_REF  11
#define CONSTANT_NAME_TYPE             12

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;

#endif