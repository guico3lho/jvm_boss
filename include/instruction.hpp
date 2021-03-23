
#ifndef JVM_CPP_INSTRUCTION_H
#define JVM_CPP_INSTRUCTION_H

#include <string>
#include "read_bytes.hpp"

/* INSTRUCTIONS */

/* CONSTANTS */
#define ldc 18
#define ldc_w 19
#define ldc2_w 20

/* COMPARISONS */
#define iifeq 153
#define ifne 154
#define iflt 155
#define ifge 156
#define ifgt 157
#define ifle 158
#define if_icmpeq 159
#define if_icmpne 160
#define if_icmplt 161
#define if_icmpge 162
#define if_icmpgt 163
#define if_icmple 164
#define if_acmpeq 165
#define if_acmpne 166

/* CONTROL */
#define GOTO 167
#define jsr 168

/* REFERENCES */
#define getstatic 178
#define putstatic 179
#define getfield 180
#define putfield 181
#define invokevirtual 182
#define invokespecial 183
#define invokestatic 184
#define invokeinterface 185
#define invokedynamic 186
#define NEW 187
#define newarray 188
#define anewarray 189
#define checkcast 192
#define instanceof 193

/* EXTENDED */
#define multianewarray 197
#define ifnull 198
#define ifnonull 199

/* ATYPE OF EACH NEWARRAY */
#define T_BOOLEAN 0x4
#define T_CHAR    0x5
#define T_FLOAT	  0x6
#define T_DOUBLE	0x7
#define T_BYTE    0x8
#define T_SHORT	  0x9
#define T_INT     0x10
#define T_LONG    0x11

typedef struct Instruction {
  std::string name;
  u4 bytes;
  u4 constant_pool_flag;
} Instruction;

Instruction *set_instructions();

#endif
