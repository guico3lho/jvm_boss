/** 
 *  @file class_loader.hpp
 *  @brief Estruturas e declarações de funções do Class Loader da JVM.
*/

#ifndef __CLASS_LOADER_H__
#define __CLASS_LOADER_H__

#include <map>
#include "class_file.hpp"
#include "frame.hpp"

struct Operand;

/** 
 * @brief Estrutura para instanciar a classe
 */
typedef struct Class_Loader{
    std::string *class_name = nullptr;

    Class_File class_file;

    // vetor com as referencias dos campos da classe
    std::map<std::string, Operand*> *class_fields;
} Class_Loader; 

Class_Loader* load_class_memory(Class_File class_file);
void load_class_var(Class_Loader *class_loader);
Class_File get_class_info_and_load_not_exists(std::string c_path);
Class_Loader* get_static_class(std::string class_name);

Operand* get_static_field_of_class(std::string class_name, std::string field_name);
Operand* check_string_create_type(std::string string_tipo);

#endif