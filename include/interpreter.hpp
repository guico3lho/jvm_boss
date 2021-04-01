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

struct Class_Loader;
struct Instruction;
struct Operand;

void execute(Class_File class_file);

Class_Loader* load_class_memory(Class_File class_file);
Class_Loader* get_static_class(std::string class_name);

Class_File get_class_info_and_load_not_exists(std::string class_path);

Operand* get_static_field_of_class(std::string class_name, std::string field_name);



#endif