#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

#include "class_file.hpp"
#include "class_loader.hpp"
#include "instruction.hpp"

#include <vector>

struct Class_Loader;
struct Operand;

void execute(Class_File class_file);



#endif // !_INTERPRETER_H_

