/** @file interpreter.h
 *  @brief Estruturas e declarações de funções do interpretador da JVM.
 *  @bug No know bugs.
 */
#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include <sstream>
#include <cmath>

#include "class_file.hpp"
#include "class_loader.hpp"
#include "instruction.hpp"

void execute(Class_File class_file);

#endif