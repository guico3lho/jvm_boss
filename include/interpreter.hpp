#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

#include "class_file.hpp"
#include "class_loader.hpp"

void execute(Class_File class_file);
Class_Loader * load_class_memory(Class_File class_file);


#endif // !_INTERPRETER_H_

