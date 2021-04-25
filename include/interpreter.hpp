/** 
 *  @file interpreter.hpp
 *  @brief Estruturas e declarações de funções do interpretador da JVM.
 */

#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include <sstream>
#include <cmath>

#include "class_file.hpp"
#include "method_area.hpp"


void execute(Class_File class_file);

#endif