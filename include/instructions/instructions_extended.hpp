/** 
 *  @file instructions_extended.hpp
 *  @brief Declaração das funções de cada instrução extendida de opcode da JVM
 */

#ifndef __INSTRUCTIONS_EXTENDED_H__
#define __INSTRUCTIONS_EXTENDED_H__

#include "frame.hpp"

/* EXTENDED */
void multianewarray(Frame*);
Operand* set_multianewarray(Operand* operand, int count, string array_type);

void ifnull(Frame*);
void ifnonnull(Frame*);

#endif
