/** 
 *  @file instructions_func.h
 *  @brief Declaração das funções de cada instrução de opcode 
 * 
 */
#ifndef __INSTRUCTIONS_FUNC_H__
#define __INSTRUCTIONS_FUNC_H__

#include "frame.hpp"



/* REFERENCES */
void getstatic(Frame*);
void getfield(Frame*);
void putfield(Frame*);

void invokevirtual(Frame*);
void invokespecial(Frame*);
void invokestatic(Frame*);
void invokeinterface(Frame*);

void new_obj(Frame*);
void newarray(Frame*);
void arraylength(Frame* );

/* CONTROL */
void ins_goto(Frame*);
void ret(Frame*);
void tableswitch(Frame*);
void lookupswitch(Frame*);

void ireturn(Frame*);
void lreturn(Frame*);
void freturn(Frame*);
void dreturn(Frame*);
void areturn(Frame*);
void void_return(Frame*);

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

/* EXTENDED */
void ifnull(Frame*);
void ifnonnull(Frame*);


#endif
