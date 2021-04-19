/** 
 *  @file instructions_constant.hpp
 *  @brief Declaração das funções de instruções de opcode de tipos de constantes da JVM
 * 
 */
#ifndef __INSTRUCTIONS_CONSTANT_H__
#define __INSTRUCTIONS_CONSTANT_H__

#include "frame.hpp"

/* CONSTANTS */
void nop(Frame*);
void aconst_null(Frame*);

void iconst_m1(Frame*);
void iconst_0(Frame*);
void iconst_1(Frame*);
void iconst_2(Frame*);
void iconst_3(Frame*);
void iconst_4(Frame*);
void iconst_5(Frame*);

void lconst_0(Frame*);
void lconst_1(Frame*);

void fconst_0(Frame*);
void fconst_1(Frame*);
void fconst_2(Frame*);

void dconst_0(Frame*);
void dconst_1(Frame*);

void bipush(Frame*);
void sipush(Frame*);

void ldc_w(Frame*);
void ldc2_w(Frame*);
void ldc(Frame*);

#endif
