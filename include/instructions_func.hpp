/** 
 *  @file instructions_func.h
 *  @brief Declaração das funções de cada instrução de opcode 
 * 
 */
#ifndef __INSTRUCTIONS_FUNC_H__
#define __INSTRUCTIONS_FUNC_H__

#include "frame.hpp"


void invokespecial(Frame*);
void invokevirtual(Frame*);
void getstatic(Frame*);
void getfield(Frame*);
void void_return(Frame*);

void iinc(Frame*);
void dadd(Frame*);
void dsub(Frame*);
void dmul(Frame*);
void ddiv(Frame*);
void f2d(Frame*);
void f2i(Frame*);
void l2d(Frame*);
void l2f(Frame*);
void l2i(Frame*);
void i2f(Frame*);
void i2s(Frame*);
void l2f(Frame*);
void d2f(Frame*);
void iadd(Frame*);
void iand(Frame*);
void d2f(Frame*);
void d2l(Frame*);
void d2i(Frame*);
void ior(Frame*);
void dup_x1(Frame*);
void dup_x2(Frame*);
void dup2(Frame*);
void dup2_x1(Frame*);
void dup2_x2(Frame*);
void f2l(Frame*);
void ladd(Frame*);
void lsub(Frame*);
void ldiv(Frame*);


void pop(Frame*);
void pop2(Frame*);


void if_icmpge(Frame*);
void ins_goto(Frame*);
void i2l(Frame*);
void i2d(Frame*);
void invokestatic(Frame*);
void lreturn(Frame*);
void new_obj(Frame*);
void dup(Frame*);

void putfield(Frame*);



void isub(Frame*);
void invokeinterface(Frame*);
void areturn(Frame*);
void dreturn(Frame*);
void freturn(Frame*);
void ireturn(Frame*);

void fadd(Frame*);
void fsub(Frame*);
void fdiv(Frame*);
void fmul(Frame*);
void frem(Frame*);
void drem(Frame*);
void fneg(Frame*);
void lookupswitch(Frame*);
void iconst_m1(Frame*);

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

void swap(Frame*);
void imul(Frame*);
void lmul(Frame*);
void idiv(Frame*);
void irem(Frame*);
void lrem(Frame*);
void ineg(Frame*);
void lneg(Frame*);
void dneg(Frame*);
void ishl(Frame*);
void lshl(Frame*);
void ishr(Frame*);
void lshr(Frame*);
void iushr(Frame*);
void lushr(Frame*);
void land(Frame*);
void lor(Frame*);
void ixor(Frame*);
void lxor(Frame*);

void iinc(Frame*);
void ifnull(Frame*);
void ifnonnull(Frame*);

void ret(Frame*);

void tableswitch(Frame*);

#endif
