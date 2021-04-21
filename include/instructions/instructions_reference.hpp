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
void invokevirtual_print(Frame *curr_frame, string method_name);
void invokevirtual_string_builder_append(Frame *curr_frame);
void invokevirtual_not_default_java(Frame *curr_frame, string method_name, string method_desc);

void invokespecial(Frame*);
void invokestatic(Frame*);
void invokeinterface(Frame*);

void new_obj(Frame*);
void newarray(Frame*);
void set_newarray_type(Operand *operand, u4 index, string array_type);
void arraylength(Frame*);

#endif
