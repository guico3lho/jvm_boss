/** 
 *  @file instructions_conversion.hpp
 *  @brief Declaração das funções de instruções de opcode do tipo conversion da JVM
 */

#ifndef __INSTRUCTIONS_CONVERSION_H__
#define __INSTRUCTIONS_CONVERSION_H__

#include "frame.hpp"

/* CONVERSION */
void i2l(Frame*);
void i2f(Frame*);
void i2d(Frame*);
void i2b(Frame*);
void i2c(Frame*);
void i2s(Frame*);

void l2i(Frame*);
void l2f(Frame*);
void l2d(Frame*);

void f2i(Frame*);
void f2l(Frame*);
void f2d(Frame*);

void d2i(Frame*);
void d2l(Frame*);
void d2f(Frame*);


#endif
