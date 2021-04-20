/** 
 *  @file instructions_stack.hpp
 *  @brief Declaração das funções de instruções de opcode do tipo stack da JVM
 */

#ifndef __INSTRUCTIONS_STACK_H__
#define __INSTRUCTIONS_STACK_H__

#include "frame.hpp"

/* STACK */
void pop(Frame*);
void pop2(Frame*);
void dup(Frame*);
void dup_x1(Frame*);
void dup_x2(Frame*);
void dup2(Frame*);
void dup2_x1(Frame*);
void dup2_x2(Frame*);
void swap(Frame*);

#endif
