/** 
 *  @file instruction.hpp
 *  @brief Estruturas, declaração de funções e definições de constanstes relacionadas a instruções
 */

#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include <string>
#include <vector>
#include "read_bytes.hpp"

/* INSTRUCTIONS */

/* CONSTANTS */
#define CONSTANT_ldc 18
#define CONSTANT_ldc_w 19
#define CONSTANT_ldc2_w 20

/* COMPARISONS */
#define CONSTANT_iifeq 153
#define CONSTANT_ifne 154
#define CONSTANT_iflt 155
#define CONSTANT_ifge 156
#define CONSTANT_ifgt 157
#define CONSTANT_ifle 158
#define CONSTANT_if_icmpeq 159
#define CONSTANT_if_icmpne 160
#define CONSTANT_if_icmplt 161
#define CONSTANT_if_icmpge 162
#define CONSTANT_if_icmpgt 163
#define CONSTANT_if_icmple 164
#define CONSTANT_if_acmpeq 165
#define CONSTANT_if_acmpne 166

/* CONTROL */
#define CONSTANT_GOTO 167
#define CONSTANT_jsr 168

/* REFERENCES */
#define CONSTANT_getstatic 178
#define CONSTANT_putstatic 179
#define CONSTANT_getfield 180
#define CONSTANT_putfield 181
#define CONSTANT_invokevirtual 182
#define CONSTANT_invokespecial 183
#define CONSTANT_invokestatic 184
#define CONSTANT_invokeinterface 185
#define CONSTANT_invokedynamic 186
#define CONSTANT_NEW 187
#define CONSTANT_newarray 188
#define CONSTANT_anewarray 189
#define CONSTANT_checkcast 192
#define CONSTANT_instanceof 193

/* EXTENDED */
#define CONSTANT_multianewarray 197
#define CONSTANT_ifnull 198
#define CONSTANT_ifnonull 199

/* ATYPE OF EACH NEWARRAY */
#define T_BOOLEAN 0x4
#define T_CHAR    0x5
#define T_FLOAT	  0x6
#define T_DOUBLE	0x7
#define T_BYTE    0x8
#define T_SHORT	  0x9
#define T_INT     0x10
#define T_LONG    0x11

/** 
 *  @brief Estrutura de dados que armazena uma Instruction
 */
typedef struct Instruction {
  std::string name;
  u4 bytes;
} Instruction;

std::vector<Instruction> set_instructions();

#endif
