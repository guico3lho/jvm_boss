/** 
 *  @file instructions_store.hpp
 *  @brief Declaração das funções de instruções de opcode do tipo store da JVM
 */

#ifndef __INSTRUCTIONS_STORE_H__
#define __INSTRUCTIONS_STORE_H__

#include "frame.hpp"

/* STORE */
void istore(Frame*);
void istore_0(Frame*);
void istore_1(Frame*);
void istore_2(Frame*);
void istore_3(Frame*);

void lstore(Frame*);
void lstore_0(Frame*);
void lstore_1(Frame*);
void lstore_2(Frame*);
void lstore_3(Frame*);

void fstore(Frame*);
void fstore_0(Frame*);
void fstore_1(Frame*);
void fstore_2(Frame*);
void fstore_3(Frame*);

void dstore(Frame*);
void dstore_0(Frame*);
void dstore_1(Frame*);
void dstore_2(Frame*);
void dstore_3(Frame*);

void astore(Frame*);
void astore_0(Frame*);
void astore_1(Frame*);
void astore_2(Frame*);
void astore_3(Frame*);

void iastore(Frame*);
void lastore(Frame*);
void fastore(Frame*);
void dastore(Frame*);
void aastore(Frame*);
void bastore(Frame*);
void castore(Frame*);
void sastore(Frame*);

#endif
