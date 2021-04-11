#ifndef _CLASS_LOADER_H_
#define _CLASS_LOADER_H_

#include "class_file.hpp"
#include "frame.hpp"
#include <string>
#include <map>

typedef struct Class_Loader
{
    std::string *class_name;

    Class_File class_file;

    std::map<std::string, Operand *> *class_fields;
} Class_Loader;

void load_class_var(Class_Loader *class_loader);
Class_File get_class_info_and_load_not_exists(std::string c_path);
Class_Loader* load_class_memory(Class_File class_file);

#endif