/** @file frame.hpp
 *  @brief Estruturas e classes de Frames e Operandos
 */

#ifndef __FRAME_H__
#define __FRAME_H__

#include <stack>
#include <vector>
#include "method_area.hpp"
#include "interpreter.hpp"

using std::cout;
using std::string;

struct Class_Container;
struct Array_Type;

/** 
 *  @brief Estrutura de dados que armazena um operando
 */
typedef struct Operand {
  u1 tag; 
  union{
    u4 type_int;
    u4 type_float;
    u8 type_long;
    u8 type_double;

    u4 type_bool;
    u4 type_byte;
    u4 type_char;
    u4 type_short;
    
    string       *type_string;
    Array_Type   *array_type;
    Class_Container *class_container;
  };
} Operand;

/** 
 *  @brief Estrutura de dados que armazena o tipo do operando
 */
typedef struct Array_Type{  
  std::vector<Operand*> *array;
} Array_Type;

/**
  * @brief Estrutura de dados que armazena informações e resultados parciais, para executar
  *  ligação dinâmica,retornar valores para métodos e disparar exceções.
  * 
  *  Cada frame possui sua pilha de operandos, seu próprio vetor de variáveis locais e 
  *  uma referência para o pool de constantes da classe do método corrente.
  * 
  **/
class Frame {
public:
  Frame(Method_Info*, Class_File);

  std::stack<Operand*> operand_stack;
  std::vector<Operand*> local_variables_array;

  Class_File* class_file_ref = nullptr;
  Cp_Info* cp_reference = nullptr;
  Method_Info* method_info = nullptr;
  Code_Attribute* method_code = nullptr;
  u4 pc;

  void execute_frame();
  Operand* pop_operand();
  void push_operand(Operand* op);
  static void set_instructions_functions();
};

Frame* top_frame();
void push_frame(Frame* frame);
void pop_frame();

u2 get_method_code_index(Frame*);
Operand* copy_operand(Operand* original_operand);

#endif