/** 
 *  @file method_area.hpp
 *  @brief Estruturas e declarações para a method_area
*/
#ifndef __METHOD_AREA_H__
#define __METHOD_AREA_H__

#include <map>
#include "class_file.hpp"
#include "frame.hpp"

struct Operand;

/** 
 * @brief Estrutura para guardar informações sobre o class_file que fará parte do method_area
 */
typedef struct Class_Container {
    Class_File class_file;

    // vetor com as referencias dos campos da classe
    std::map<std::string, Operand *> *class_fields;
} Class_Container;       

/**
 * @brief Estrutura utilizada para guardar informações sobre classes carregadas na memória, 
 * através de estruturas de maps, contendo chave e valor de cada classe estática ou não
 * 
 */
typedef struct Method_Area {
    std::map<std::string, Class_Container *> loaded_classes;
    std::map<std::string, Class_Container *> static_classes;
} Method_Area;

/** 
 *  @brief Funções do class_loader
*/
Method_Area *load_class_memory(Class_File class_file);
void load_class_variables(Class_Container* class_container);
Class_File load_parent_classes(std::string c_path);

/** 
 *  @brief Funções auxiliares
*/
Class_Container *get_static_class(std::string class_name);
Operand *get_static_field_of_class(std::string class_name, std::string field_name);
Operand *check_string_create_type(std::string string_tipo);

/** 
 *  @brief Função para encontrar a main
*/
Method_Info* find_main(Method_Area* method_area);

#endif