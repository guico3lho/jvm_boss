/** 
 *  @file instructions_store.cpp
 *  @brief Módulo que contém as instruções de opcode do tipo store da JVM.
*/

#include "interpreter.hpp"

/*************************** STORES ***************************/

/**
 * @brief Armazena um inteiro no array de variaveis locais no valor indicado
 *   pelo indice.
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
*/
void istore(Frame* curr_frame) {
  if (DEBUG) cout << "----------istore----------\n";  
  curr_frame->pc++;

  u1 index = curr_frame->method_code->code[curr_frame->pc++];
  if (DEBUG) cout << "istore index " << (int) index << "\n";

  Operand* value = curr_frame->pop_operand();
  curr_frame->local_variables_array.at((int) index) = value;
}

/**
 * @brief Armazena um inteiro no array de variaveis locais no indice 0
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void istore_0(Frame* curr_frame) {
  if (DEBUG) cout << "----------istore_0----------\n";  

  Operand* value = curr_frame->pop_operand();
  curr_frame->local_variables_array.at(0) = value;
  curr_frame->pc++;
}

/**
 * @brief Armazena um inteiro no array de variaveis locais no indice 1
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void istore_1(Frame* curr_frame) {
  if (DEBUG) cout << "----------istore_1----------\n";  

  Operand* value = curr_frame->pop_operand();
  curr_frame->local_variables_array.at(1) = value;
  curr_frame->pc++;
}

/**
 * @brief Armazena um inteiro no array de variaveis locais no indice 2
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void istore_2(Frame* curr_frame) {
  if (DEBUG) cout << "----------istore_2----------\n";  

  Operand* value = curr_frame->pop_operand();
  curr_frame->local_variables_array.at(2) = value;
  curr_frame->pc++;
}

/**
 * @brief Armazena um inteiro no array de variaveis locais no indice 0
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void istore_3(Frame* curr_frame) {
  if (DEBUG) cout << "----------istore_3----------\n";  

  Operand* value = curr_frame->pop_operand();
  curr_frame->local_variables_array.at(3) = value;
  curr_frame->pc++;
}

/**
* @brief ...
* @param *curr_frame ponteiro para o frame atual
* @return void
*/
void astore(Frame* curr_frame) {
  if (DEBUG) cout << "----------astore----------\n";
  curr_frame->pc++;

  u1 index = curr_frame->method_code->code[curr_frame->pc++];
  Operand* operand = curr_frame->pop_operand();
  curr_frame->local_variables_array.at(index) = operand;
}

/** @brief Guarda referência do object ou array do operando na variável local -0.
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void astore_0(Frame* curr_frame) {
  if (DEBUG) cout << "----------astore_0----------\n";
  curr_frame->pc++;

  Operand* op = curr_frame->pop_operand();
  curr_frame->local_variables_array.at(0) = op;
}

/** @brief Guarda referência do object ou array do operando na variável local 1.
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void astore_1(Frame* curr_frame) {
  if (DEBUG) cout << "----------astore_1----------\n";
  curr_frame->pc++;

  Operand* op = curr_frame->pop_operand();
  curr_frame->local_variables_array.at(1) = op;
}

/** @brief Retira o topo da pilha e armazena na variavel local de posição 2.
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void astore_2(Frame* curr_frame) {
  if (DEBUG) cout << "----------astore_2----------\n";
  curr_frame->pc++;

  Operand* op = curr_frame->pop_operand();
  curr_frame->local_variables_array.at(2) = op;
  if (DEBUG) cout << "astore_2\n";
}

/** @brief Retira o topo da pilha e armazena na variavel local de posição 3.
  * @param curr_frame ponteiro para o frame atual
  * @return void
*/
void astore_3(Frame* curr_frame) {
  if (DEBUG) cout << "----------astore_3----------\n";
    curr_frame->pc++;

    Operand* op = curr_frame->pop_operand();
    curr_frame->local_variables_array.at(3) = op;
}

/**
 * @brief Armazena valor double da pilha de operandos no array de variaveis
 *  locais no indice index
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void dstore(Frame* curr_frame) {
  if (DEBUG) cout << "----------dstore----------\n";
  curr_frame->pc++;

  u1 index = curr_frame->method_code->code[curr_frame->pc++];
  if (DEBUG) cout << "dstore index " << (int) index << "\n";
  Operand* op = curr_frame->pop_operand();

  curr_frame->local_variables_array.at((int) index) = op;
}

/**
 * @brief Armazena valor double da pilha de operandos no array de variaveis locais no indice 0
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void dstore_0(Frame* curr_frame) {
  if (DEBUG) cout << "----------dstore_0----------\n";

  Operand* op = curr_frame->operand_stack.top();
  curr_frame->operand_stack.pop();

  curr_frame->local_variables_array[0] = op;
  curr_frame->pc++;
}

/**
 * @brief Armazena valor double da pilha de operandos no array de variaveis locais no indice 1
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void dstore_1(Frame* curr_frame) {
  if (DEBUG) cout << "----------dstore_1----------\n";

  Operand* op = curr_frame->pop_operand();

  curr_frame->local_variables_array[1] = op;
  curr_frame->pc++;

  if (DEBUG) cout << "dstore_1\n";
}

/**
 * @brief Armazena valor double da pilha de operandos no array de variaveis locais no indice 2
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void dstore_2(Frame* curr_frame) {
  if (DEBUG) cout << "----------dstore_2----------\n";

  Operand* op = curr_frame->operand_stack.top();
  curr_frame->operand_stack.pop();

  curr_frame->local_variables_array[2] = op;
  curr_frame->pc++;
}

/**
 * @brief Armazena valor double da pilha de operandos no array de variaveis locais no indice 3
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void dstore_3(Frame* curr_frame) {
  if (DEBUG) cout << "----------dstore_3----------\n";

  Operand* op = curr_frame->operand_stack.top();
  curr_frame->operand_stack.pop();

  curr_frame->local_variables_array[3] = op;
  curr_frame->pc++;
}

/**
 * @brief Armazena float do topo da pilha de operandos no array de variaveis
 *  locais
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void fstore(Frame* curr_frame) {
  if (DEBUG) cout << "----------fstore----------\n";
  curr_frame->pc++;

  u1 index = curr_frame->method_code->code[curr_frame->pc++];
  if (DEBUG) cout << "fstore index " << (int)index << "\n";
  Operand* op = curr_frame->pop_operand();

  curr_frame->local_variables_array[(int)index] = op;
}

/**
 * @brief Armazena float do topo da pilha de operandos no array de variaveis locais no indice 0
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void fstore_0(Frame* curr_frame) {
  if (DEBUG) cout << "----------fstore_0----------\n";

  Operand* op = curr_frame->operand_stack.top();
  curr_frame->operand_stack.pop();

  curr_frame->local_variables_array[0] = op;
  curr_frame->pc++;
}

/**
* @brief Armazena float do topo da pilha de operandos no array de variaveis locais no indice 1
* @param *curr_frame Ponteiro para o frame atual
* @return void
*/
void fstore_1(Frame* curr_frame) {
  if (DEBUG) cout << "----------fstore_1----------\n";

  Operand* op = curr_frame->operand_stack.top();
  curr_frame->operand_stack.pop();

  curr_frame->local_variables_array[1] = op;
  curr_frame->pc++;
}

/**
* @brief Armazena float do topo da pilha de operandos no array de variaveis locais no indice 2
* @param *curr_frame Ponteiro para o frame atual
* @return void
*/
void fstore_2(Frame* curr_frame) {
  if (DEBUG) cout << "----------fstore_2----------\n";

  Operand* op = curr_frame->operand_stack.top();
  curr_frame->operand_stack.pop();

  curr_frame->local_variables_array[2] = op;
  curr_frame->pc++;
}

/**
* @brief Armazena float do topo da pilha de operandos no array de variaveis
* locais no indice 3
* @param *curr_frame Ponteiro para o frame atual
* @return void
*/
void fstore_3(Frame* curr_frame) {
  if (DEBUG) cout << "----------fstore_3----------\n";

   Operand* op = curr_frame->pop_operand();

  curr_frame->local_variables_array[3] = op;
  curr_frame->pc++;

  if (DEBUG) cout << "fstore_3\n";
}

/*
* @brief Armazena long do topo da pilha de operandos no array de variaveis
*   locais no indice index
* @param *curr_frame Ponteiro para o frame atual
* @return void
*/
void lstore(Frame* curr_frame) {
  if (DEBUG) cout << "----------lstore----------\n";

  curr_frame->pc++;

  u1 index = curr_frame->method_code->code[curr_frame->pc++];
  if (DEBUG) cout << "lstore index " << (int)index << "\n";
  Operand* op = curr_frame->pop_operand();

  curr_frame->local_variables_array.at((int)index) = op;

  if (DEBUG) cout << "lstore\n";
}

/**
* @brief Armazena long do topo da pilha de operandos no array de variaveis locais no indice 0
* @param curr_frame Ponteiro para o frame atual
* @return void
*/
void lstore_0(Frame* curr_frame) {
  if (DEBUG) cout << "----------lstore_0----------\n";

  Operand* op = curr_frame->operand_stack.top();
  curr_frame->operand_stack.pop();

  curr_frame->local_variables_array[0] = op;
  curr_frame->pc++;
}

/**
* @brief Armazena long do topo da pilha de operandos no array de variaveis locais no indice 1
* @param curr_frame Ponteiro para o frame atual
* @return void
*/
void lstore_1(Frame* curr_frame) {
  if (DEBUG) cout << "----------lstore_1----------\n";

  Operand* op = curr_frame->operand_stack.top();
  curr_frame->operand_stack.pop();

  curr_frame->local_variables_array[1] = op;
  curr_frame->pc++;
  if (DEBUG) cout << "lstore_1\n";

}

/**
* @brief Armazena long do topo da pilha de operandos no array de variaveis locais no indice 2
* @param curr_frame Ponteiro para o frame atual
* @return void
*/
void lstore_2(Frame* curr_frame) {
  if (DEBUG) cout << "----------lstore_2----------\n";

  Operand* op = curr_frame->operand_stack.top();
  curr_frame->operand_stack.pop();

  curr_frame->local_variables_array[2] = op;
  curr_frame->pc++;
}

/**
* @brief Armazena long do topo da pilha de operandos no array de variaveis locais no indice 3
* @param curr_frame Ponteiro para o frame atual
* @return void
*/
void lstore_3(Frame* curr_frame) {
  if (DEBUG) cout << "----------lstore_3----------\n";

  Operand* op = curr_frame->operand_stack.top();
  curr_frame->operand_stack.pop();

  curr_frame->local_variables_array[3] = op;
  curr_frame->pc++;
  if (DEBUG) cout << "lstore_3\n";
}

/**
 * @brief Coleta um int da pilha de operandos e armazena em um vetor de ints.
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void iastore(Frame* curr_frame) {
  if (DEBUG) cout << "----------iastore----------\n";

  Operand* value = curr_frame->pop_operand();
  Operand* index = curr_frame->pop_operand();
  Operand* array = curr_frame->pop_operand();

  ((*array->array_type->array)[(int)index->type_int])->type_int = value->type_int;

  if (DEBUG) cout << "iastore value : " << value->type_int << "\n";
  if (DEBUG)
    for (int j=0; (unsigned)j < array->array_type->array->size(); ++j) {
      int value = (array->array_type->array->at(j))->type_int;
      if (DEBUG) cout << "array item : " << value << "\n";
    }

  curr_frame->push_operand(array);
  curr_frame->pc++;

  if (DEBUG) cout << "iastore\n";
}

/**
 * @brief Coleta um long da pilha de operandos e armazena em um vetor de longs.
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void lastore(Frame* curr_frame) {
  if (DEBUG) cout << "----------lastore----------\n";

  Operand* value = curr_frame->pop_operand();
  Operand* index = curr_frame->pop_operand();
  Operand* array = curr_frame->pop_operand();

  ((*array->array_type->array)[(int)index->type_int])->type_long = value->type_long;

  if (DEBUG) cout << "lastore value : " << value->type_long << "\n";
  if (DEBUG)
    for (int j=0; (unsigned)j < array->array_type->array->size(); ++j) {
      int value = (array->array_type->array->at(j))->type_long;
      if (DEBUG) cout << "array item : " << value << "\n";
    }

  curr_frame->push_operand(array);
  curr_frame->pc++;

  if (DEBUG) cout << "lastore\n";
}

/**
 * @brief Coleta um float da pilha de operandos e armazena em um vetor de floats.
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void fastore(Frame* curr_frame) {
  if (DEBUG) cout << "----------fastore----------\n";

  Operand* value = curr_frame->pop_operand();
  Operand* index = curr_frame->pop_operand();
  Operand* array = curr_frame->pop_operand();

  if (DEBUG) cout << "fastore value: " << value->type_float << "\n";
  ((*array->array_type->array)[(int)index->type_int])->type_float = value->type_float;

  if (DEBUG)
    for (int j=0; (unsigned) j < array->array_type->array->size(); ++j) {
      int value = (array->array_type->array->at(j))->type_float;
      if (DEBUG) cout << "array item : " << value << "\n";
    }

  curr_frame->push_operand(array);
  curr_frame->pc++;
}

/**
 * @brief Coleta um double da pilha de operandos e armazena em um vetor de doubles.
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void dastore(Frame* curr_frame) {
  if (DEBUG) cout << "----------dastore----------\n";

  Operand* value = curr_frame->pop_operand();
  Operand* index = curr_frame->pop_operand();
  Operand* array = curr_frame->pop_operand();

  ((*array->array_type->array)[(int)index->type_int])->type_double = value->type_double;

  if (DEBUG) cout << "dastore value : " << value->type_double << "\n";
  if (DEBUG)
    for (int j=0; (unsigned)j < array->array_type->array->size(); ++j) {
      int value = (array->array_type->array->at(j))->type_double;
      if (DEBUG) cout << "array item : " << value << "\n";
    }

  curr_frame->push_operand(array);
  curr_frame->pc++;

  if (DEBUG) cout << "dastore\n";
}

/**
 * @brief Coleta um objeto da pilha de operandos e armazena em um vetor de objetos.
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void aastore(Frame* curr_frame) {
  if (DEBUG) cout << "----------aastore----------\n";

  Operand* value = curr_frame->pop_operand();
  // if (DEBUG) cout << "aastore value: " << (int) value->array_type << "\n";

  Operand* op1 = curr_frame->pop_operand();
  int index = (int) op1->type_int;
  if (DEBUG) cout << "aastore index: " << (int) index << "\n";

  Operand* array = curr_frame->pop_operand();
  std::vector<Operand*> *array_ref = array->array_type->array;

  ((*array_ref)[index])->array_type = value->array_type;

  if (DEBUG)
    for (int j = 0; (unsigned)j < array_ref->size(); ++j) {
      int sub_array_size = (array_ref->at(j))->array_type->array->size();
      if (DEBUG) cout << "sub array size: " << sub_array_size << "\n";
    }

  curr_frame->push_operand(array);
  curr_frame->pc++;
}

/**
 * @brief Coleta um booleano da pilha de operandos e armazena em um vetor de booleanos.
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void bastore(Frame* curr_frame) {
  if (DEBUG) cout << "----------bastore----------\n";

  Operand* value = curr_frame->pop_operand();
  Operand* index = curr_frame->pop_operand();
  Operand* array = curr_frame->pop_operand();

  ((*array->array_type->array)[(int)index->type_int])->type_bool = value->type_bool;

  if (DEBUG) cout << "bastore value : " << value->type_bool << "\n";
  if (DEBUG)
    for (int j=0; (unsigned)j < array->array_type->array->size(); ++j) {
      int value = (array->array_type->array->at(j))->type_bool;
      if (DEBUG) cout << "array item : " << value << "\n";
    }

  curr_frame->push_operand(array);
  curr_frame->pc++;

  if (DEBUG) cout << "bastore\n";
}

/**
 * @brief Coleta um 32-bit integer da pilha de operandos e armazena em um vetor
 *  16-bit unsigned (char).
 * @param curr_frame ponteiro para o frame atual
 * @return void
 */
void castore(Frame* curr_frame) {
  if (DEBUG) cout << "----------castore----------\n";

  Operand* value = curr_frame->pop_operand();
  Operand* index = curr_frame->pop_operand();
  Operand* array = curr_frame->pop_operand();

  ((*array->array_type->array)[(int)index->type_int])->type_char = value->type_char;

  if (DEBUG) cout << "castore value : " << value->type_char << "\n";
  if (DEBUG)
    for (int j=0; (unsigned)j < array->array_type->array->size(); ++j) {
      int value = (array->array_type->array->at(j))->type_char;
      if (DEBUG) cout << "array item : " << value << "\n";
    }

  curr_frame->push_operand(array);
  curr_frame->pc++;

  if (DEBUG) cout << "castore\n";
}

/**
 * @brief Coleta um short da pilha de operandos e armazena em um vetor shorts
 * @param curr_frame ponteiro para o frame atual
 * @return void
 */
void sastore(Frame* curr_frame) {
  if (DEBUG) cout << "----------sastore----------\n";

  Operand* value = curr_frame->pop_operand();
  Operand* index = curr_frame->pop_operand();
  Operand* array = curr_frame->pop_operand();

  ((*array->array_type->array)[(int)index->type_int])->type_short = value->type_short;

  if (DEBUG) cout << "sastore value : " << value->type_short << "\n";
  if (DEBUG)
    for (int j=0; (unsigned)j < array->array_type->array->size(); ++j) {
      int value = (array->array_type->array->at(j))->type_short;
      if (DEBUG) cout << "array item : " << value << "\n";
    }

  curr_frame->push_operand(array);
  curr_frame->pc++;

  if (DEBUG) cout << "sastore\n";
}
