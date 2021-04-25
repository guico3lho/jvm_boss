/** 
 *  @file instructions_load.hpp
 *  @brief Declaração das funções de instruções de opcode do tipo load da JVM
 */

#ifndef __INSTRUCTIONS_LOAD_H__
#define __INSTRUCTIONS_LOAD_H__

#include "frame.hpp"

/* LOAD */
void iload(Frame*);
void iload_0(Frame*);
void iload_1(Frame*);
void iload_2(Frame*);
void iload_3(Frame*);

void lload(Frame*);
void lload_0(Frame*);
void lload_1(Frame*);
void lload_2(Frame*);
void lload_3(Frame*);

void fload(Frame*);
void fload_0(Frame*);
void fload_1(Frame*);
void fload_2(Frame*);
void fload_3(Frame*);

void dload(Frame*);
void dload_0(Frame*);
void dload_1(Frame*);
void dload_2(Frame*);
void dload_3(Frame*);

void aload(Frame*);
void aload_0(Frame*);
void aload_1(Frame*);
void aload_2(Frame*);
void aload_3(Frame*);

void iaload(Frame*);
void laload(Frame*);
void faload(Frame*);
void daload(Frame*);
void aaload(Frame*);
void baload(Frame*);
void caload(Frame*);
void saload(Frame*);

#endif
