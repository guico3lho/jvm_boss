/** @file Frame.h
 *  @brief ...
 *  @bug No know bugs.
 */
#ifndef __FRAME_H__
#define __FRAME_H__

#include <stack>
#include <vector>
#include "class_loader.hpp"

struct Class_Loader;
struct Array_Type;

typedef struct Operand {
  u1 tag; // CONSTANT_Integer, CONSTANT_Float, etc
  union{
    u4 type_bool;
    u4 type_byte;
    u4 type_char;
    u4 type_short;
    u4 type_int;
    u4 type_float;
    u8 type_long;
    u8 type_double;
    std::string* type_string;
    Class_Loader *class_loader;
    Array_Type *array_type;
  };
} Operand;

typedef struct Array_Type{  
  std::vector<Operand*> *array;
} Array_Type;

/**
  * @brief O Frame armazena dados e resultados parciais, para executar
  *  ligação dinâmica,retornar valores para métodos e disparar exceções.
  * 
  *  Cada frame possui seu próprio array de variáveis locais, sua pilha de
  *  operandos e uma referência para o pool de constantes da classe do método
  *  corrente.
  **/
class Frame {
public:
  Frame(Method_Info*, Class_File);

  std::vector<Operand*> local_variables_array;
  std::stack<Operand*> operand_stack;

  Cp_Info* constant_pool_reference;
  Class_File* class_file_ref;
  Code_Attribute* method_code;
  Method_Info* method_info;
  u4 pc;

  void execute_frame();
  Operand* pop_operand();
  void push_operand(Operand* op);
  static void setup_instructions_func();
};

Operand* copy_operand(Operand* original_operand);
Operand* check_string_create_type(std::string string_tipo);

Method_Info* find_method(Class_File class_file, std::string method_name, std::string method_desc);
Method_Info* find_main(Class_File class_file);

#endif