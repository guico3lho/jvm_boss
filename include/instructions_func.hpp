/** 
 *  @file instructions_func.h
 *  @brief Declaração das funções de cada instrução de opcode 
 * 
 */
#ifndef __INSTRUCTIONS_FUNC_H__
#define __INSTRUCTIONS_FUNC_H__

#include "frame.hpp"





void f2d(Frame*);
void f2i(Frame*);
void l2d(Frame*);
void l2f(Frame*);
void l2i(Frame*);
void i2f(Frame*);
void i2s(Frame*);
void l2f(Frame*);
void d2f(Frame*);
void d2f(Frame*);
void d2l(Frame*);
void d2i(Frame*);
void f2l(Frame*);


void invokespecial(Frame*);
void invokevirtual(Frame*);
void getstatic(Frame*);
void getfield(Frame*);
void void_return(Frame*);


void if_icmpge(Frame*);
void ins_goto(Frame*);
void i2l(Frame*);
void i2d(Frame*);
void lreturn(Frame*);
void new_obj(Frame*);




void putfield(Frame*);
void invokestatic(Frame*);
void invokeinterface(Frame*);
void areturn(Frame*);
void dreturn(Frame*);
void freturn(Frame*);
void ireturn(Frame*);


void lookupswitch(Frame*);

void if_icmpne(Frame*);
void if_icmpeq(Frame*);
void ifeq(Frame*);
void ifne(Frame*);
void iflt(Frame*);
void ifge(Frame*);
void ifgt(Frame*);
void ifle(Frame*);
void if_icmplt(Frame*);
void if_icmpgt(Frame*);
void if_icmple(Frame*);
void if_acmpeq(Frame*);
void if_acmpne(Frame*);

void newarray(Frame*);
void arraylength(Frame* );



void iinc(Frame*);
void ifnull(Frame*);
void ifnonnull(Frame*);

void ret(Frame*);

void tableswitch(Frame*);

#endif
