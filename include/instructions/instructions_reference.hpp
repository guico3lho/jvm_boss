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
void invokevirtual_print(Frame*);
void invokevirtual_string_builder_append(Frame*);

void invokespecial(Frame*);
void invokestatic(Frame*);
void invokeinterface(Frame*);

void new_obj(Frame*);
void newarray(Frame*);
void set_newarray_type(Operand*, u4, string);
void anewarray(Frame*);
void arraylength(Frame*);

void class_not_default_java(Frame*, string, string, string, string);
int count_method_arguments(string);

#endif
