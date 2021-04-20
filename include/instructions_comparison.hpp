/** 
 *  @file instructions_comparison.hpp
 *  @brief Declaração das funções de instruções de opcode do tipo comparação da JVM
 * 
 */
#ifndef __INSTRUCTIONS_COMPARISON_H__
#define __INSTRUCTIONS_COMPARISON_H__

#include "frame.hpp"

/* COMPARISONS */
void ifeq(Frame*);
void ifne(Frame*);
void iflt(Frame*);
void ifge(Frame*);
void ifgt(Frame*);
void ifle(Frame*);

void if_icmpeq(Frame*);
void if_icmpne(Frame*);
void if_icmplt(Frame*);
void if_icmpge(Frame*);
void if_icmpgt(Frame*);
void if_icmple(Frame*);
void if_acmpeq(Frame*);
void if_acmpne(Frame*);

#endif
