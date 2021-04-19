/** @file Frame.h
 *  @brief ...
 *  @bug No know bugs.
 */
#ifndef __FRAME_H__
#define __FRAME_H__

#include <stack>
#include <vector>
#include "class_loader.hpp"
#include "interpreter.hpp"

struct Class_Loader;
struct Array_Type;

typedef struct Operand {
  u1 tag; 
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

  Class_File* class_file_ref = nullptr;
  Cp_Info* cp_reference = nullptr;
  Method_Info* method_info = nullptr;
  Code_Attribute* method_code = nullptr;
  u4 pc;

  void execute_frame();
  Operand* pop_operand();
  void push_operand(Operand* op);
  static void setup_instructions_func();
};

Frame* top_frame();
void push_frame(Frame *frame);
void pop_frame();

Operand* copy_operand(Operand* original_operand);
Operand* check_string_create_type(std::string string_tipo);

#endif