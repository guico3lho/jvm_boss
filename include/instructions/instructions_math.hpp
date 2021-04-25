/** 
 *  @file instructions_math.hpp
 *  @brief Declaração das funções de instruções de opcode do tipo math da JVM
 */

#ifndef __INSTRUCTIONS_MATH_H__
#define __INSTRUCTIONS_MATH_H__

#include "frame.hpp"

/* MATH */
void iadd(Frame*);
void ladd(Frame*);
void fadd(Frame*);
void dadd(Frame*);

void isub(Frame*);
void lsub(Frame*);
void fsub(Frame*);
void dsub(Frame*);

void idiv(Frame*);
void ldiv(Frame*);
void fdiv(Frame*);
void ddiv(Frame*);

void imul(Frame*);
void lmul(Frame*);
void fmul(Frame*);
void dmul(Frame*);

void irem(Frame*);
void lrem(Frame*);
void frem(Frame*);
void drem(Frame*);

void ineg(Frame*);
void lneg(Frame*);
void fneg(Frame*);
void dneg(Frame*);

void ishl(Frame*);
void lshl(Frame*);
void ishr(Frame*);
void lshr(Frame*);
void iushr(Frame*);
void lushr(Frame*);

void iand(Frame*);
void land(Frame*);

void ior(Frame*);
void lor(Frame*);
void ixor(Frame*);
void lxor(Frame*);
void iinc(Frame*); 

#endif
