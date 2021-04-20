/** 
 *  @file instructions_reference.hpp
 *  @brief Declaração das funções de instruções de opcode do tipo referência da JVM
 */

#ifndef __INSTRUCTIONS_REFERENCE_H__
#define __INSTRUCTIONS_REFERENCE_H__

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
void arraylength(Frame*);

#endif
