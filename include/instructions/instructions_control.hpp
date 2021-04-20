/** 
 *  @file instructions_control.hpp
 *  @brief Declaração das funções de instruções de opcode do tipo controle da JVM
 */

#ifndef __INSTRUCTIONS_CONSTROL_H__
#define __INSTRUCTIONS_CONSTROL_H__

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

#endif
