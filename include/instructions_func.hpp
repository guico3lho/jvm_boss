/** 
 *  @file instructions_func.h
 *  @brief Declaração das funções de cada instrução de opcode 
 * 
 */
#ifndef __INSTRUCTIONS_FUNC_H__
#define __INSTRUCTIONS_FUNC_H__

#include "frame.hpp"


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



/* EXTENDED */
void ifnull(Frame*);
void ifnonnull(Frame*);


#endif
