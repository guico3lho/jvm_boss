/** 
 *  @file instructions_extended.hpp
 *  @brief Declaração das funções de cada instrução extendida de opcode da JVM
 * 
 */
#ifndef __INSTRUCTIONS_EXTENDED_H__
#define __INSTRUCTIONS_EXTENDED_H__

#include "frame.hpp"

/* EXTENDED */
void ifnull(Frame*);
void ifnonnull(Frame*);

#endif
