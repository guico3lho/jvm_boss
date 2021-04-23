/** @file instructions_load.cpp
 *  @brief Módulo que contém as instruções de opcode do tipo load da JVM.
*/

#include "interpreter.hpp"

/*************************** LOADS ***************************/

/**
 * @brief Pusha um inteiro, indicado por um indice, na pilha de operandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void iload(Frame *curr_frame) {
  if (DEBUG) cout << "----------iload----------\n";
  curr_frame->pc++;

  u1 index = curr_frame->method_code->code[curr_frame->pc++];
  if (DEBUG) cout << "iload index " << (int) index << "\n";
  curr_frame->push_operand(curr_frame->local_variables_array.at((int)index));
}

/**
 * @brief Pusha o inteiro do indice 0 na pilha de operandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void iload_0(Frame *curr_frame) {
  if (DEBUG) cout << "----------iload_0----------\n";
  curr_frame->push_operand(curr_frame->local_variables_array.at(0));
  curr_frame->pc++;
}

/**
 * @brief Pusha o inteiro do indice 1 na pilha de operandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void iload_1(Frame *curr_frame) {
  if (DEBUG) cout << "----------iload_1----------\n";
  curr_frame->push_operand(curr_frame->local_variables_array.at(1));
  curr_frame->pc++;
}

/**
 * @brief Pusha o inteiro do indice 2 na pilha de operandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void iload_2(Frame *curr_frame) {
  if (DEBUG) cout << "----------iload_2----------\n";
  curr_frame->push_operand(curr_frame->local_variables_array.at(2));
  curr_frame->pc++;
}

/**
 * @brief Pusha o inteiro do indice 3 na pilha de operandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void iload_3(Frame *curr_frame) {
  if (DEBUG) cout << "----------iload_3----------\n";
    curr_frame->push_operand(curr_frame->local_variables_array.at(3));
    curr_frame->pc++;
}

/**
 * @brief Empilha float indicado no indice index do array de variáveis locais
 *  na pilha de operandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void lload(Frame *curr_frame) {
  if (DEBUG) cout << "----------lload----------\n";
  curr_frame->pc++;

  int index = curr_frame->method_code->code[curr_frame->pc++];
  curr_frame->push_operand(curr_frame->local_variables_array[(int)index]);
}

/**
 * @brief Empilha long indicado no indice 0 do array de variáveis locais na pilha de operandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void lload_0(Frame *curr_frame) {
  if (DEBUG) cout << "----------lload_0----------\n";
  curr_frame->operand_stack.push(curr_frame->local_variables_array[0]);
  curr_frame->pc++;
}

/**
 * @brief Empilha long indicado no indice 1 do array de variáveis locais na pilha de operandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void lload_1(Frame *curr_frame) {
  if (DEBUG) cout << "----------lload_1----------\n";
  curr_frame->operand_stack.push(curr_frame->local_variables_array[1]);
  curr_frame->pc++;
}

/**
 * @brief Empilha long indicado no indice 2 do array de variáveis locais na pilha de operandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void lload_2(Frame *curr_frame) {
  if (DEBUG) cout << "----------lload_2----------\n";
  curr_frame->operand_stack.push(curr_frame->local_variables_array[2]);
  curr_frame->pc++;
}

/**
 * @brief Empilha long indicado no indice 3 do array de variáveis locais na pilha de operandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void lload_3(Frame *curr_frame) {
  if (DEBUG) cout << "----------lload_3----------\n";
  curr_frame->operand_stack.push(curr_frame->local_variables_array[3]);
  curr_frame->pc++;
}

/**
 * @brief Empilha float indicado no indice 0 do array de variáveis locais na
 *  pilha de operandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void fload(Frame *curr_frame) {
  if (DEBUG) cout << "----------fload----------\n";
  curr_frame->pc++;

  u1 index = curr_frame->method_code->code[curr_frame->pc++];
  if (DEBUG) cout << "fload index " << (int)index << "\n";
  curr_frame->push_operand(curr_frame->local_variables_array[(int)index]);
}

/**
 * @brief Empilha float indicado no indice 0 do array de variáveis locais na pilha de operandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void fload_0(Frame *curr_frame) {
  if (DEBUG) cout << "----------fload_0----------\n";
  curr_frame->operand_stack.push(curr_frame->local_variables_array[0]);
  curr_frame->pc++;
}

/**
 * @brief Empilha float indicado no indice 1 do array de variáveis locais na pilha de operandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void fload_1 (Frame *curr_frame) {
  if (DEBUG) cout << "----------fload_1----------\n";
  curr_frame->operand_stack.push(curr_frame->local_variables_array[1]);
  curr_frame->pc++;
}

/**
 * @brief Empilha float indicado no indice 2 do array de variáveis locais na pilha de operandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void fload_2 (Frame *curr_frame) {
  if (DEBUG) cout << "----------fload_2----------\n";
  curr_frame->operand_stack.push(curr_frame->local_variables_array[2]);
  curr_frame->pc++;
}

/**
 * @brief Empilha float indicado no indice 3 do array de variáveis locais na pilha de operandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void fload_3  (Frame *curr_frame) {
  if (DEBUG) cout << "----------fload_3----------\n";
  curr_frame->operand_stack.push(curr_frame->local_variables_array[3]);
  curr_frame->pc++;
}

/** @brief Dá push em um valor de preciso dupla de uma variável local para a
 *  pilha de operandos.
 * @param *curr_frame ponteiro que aponta para o frame atual
 * @return void
 */
void dload(Frame *curr_frame) {
  if (DEBUG) cout << "----------dload----------\n";
  curr_frame->pc++;

  u1 index = curr_frame->method_code->code[curr_frame->pc++];
  if (DEBUG) cout << "dload index " << (int)index << "\n";
  curr_frame->push_operand(curr_frame->local_variables_array.at((int)index));
}

/**
 * @brief empilha double  indicado no indice 0 do array de variaveis locais na pilha de operandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void dload_0(Frame *curr_frame) {
  if (DEBUG) cout << "----------dload_0----------\n";
  curr_frame->operand_stack.push(curr_frame->local_variables_array[0]);
  curr_frame->pc++;
}

/**
 * @brief empilha double  indicado no indice 1 do array de variaveis locais na pilha de operandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void dload_1(Frame *curr_frame) {
  if (DEBUG) cout << "----------dload_1----------\n";
  curr_frame->operand_stack.push(curr_frame->local_variables_array[1]);
  curr_frame->pc++;
}

/**
 * @brief empilha double  indicado no indice 2 do array de variaveis locais na pilha de operandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void dload_2(Frame *curr_frame) {
  if (DEBUG) cout << "----------dload_2----------\n";
  curr_frame->operand_stack.push(curr_frame->local_variables_array[2]);
  curr_frame->pc++;
}

/**
 * @brief empilha double  indicado no indice 3 do array de variaveis locais na pilha de operandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void dload_3(Frame *curr_frame) {
  if (DEBUG) cout << "----------dload_3----------\n";
  curr_frame->operand_stack.push(curr_frame->local_variables_array[3]);
  curr_frame->pc++;
}

/** @brief Coloca na pilha de operandos a variável da posição do pc no vetor de variáveis locais.
 * @param *curr_frame ponteiro que aponta para o frame atual
 * @return void
 */
void aload(Frame *curr_frame) {
  if (DEBUG) cout << "----------aload----------\n";
  curr_frame->pc++;

  u1 index = curr_frame->method_code->code[curr_frame->pc++];
  curr_frame->push_operand(curr_frame->local_variables_array.at(index));
}

/** @brief Coloca na pilha de operandos a variável da posição 0 do vetor de
 *          variáveis locais.
 * @param *curr_frame ponteiro que aponta para o frame atual
 * @return void
 */
void aload_0(Frame *curr_frame) {
  if (DEBUG) cout << "----------aload_0----------\n";
    curr_frame->pc++;
    curr_frame->push_operand(curr_frame->local_variables_array.at(0));
}

/** @brief Coloca na pilha de operandos a variável da posição 1 do vetor de
 *          variáveis locais.
 * @param *curr_frame ponteiro que aponta para o frame atual
 * @return void
 */
void aload_1(Frame *curr_frame) {
  if (DEBUG) cout << "----------aload_1----------\n";
  curr_frame->pc++;
  curr_frame->push_operand(curr_frame->local_variables_array.at(1));
}

/** @brief Coloca na pilha de operandos a variável da posição 2 do vetor de
 *          variáveis locais.
 * @param *curr_frame ponteiro que aponta para o frame atual
 * @return void
 */
void aload_2(Frame *curr_frame) {
  if (DEBUG) cout << "----------aload_2----------\n";
  curr_frame->pc++;
  curr_frame->push_operand(curr_frame->local_variables_array.at(2));
}

/** @brief Coloca na pilha de operandos a variável da posição 3 do vetor de
 *          variáveis locais.
 * @param *curr_frame ponteiro que aponta para o frame atual
 * @return void
 */
void aload_3(Frame *curr_frame) {
  if (DEBUG) cout << "----------aload_3----------\n";
  curr_frame->pc++;
  curr_frame->push_operand(curr_frame->local_variables_array.at(3));
}

/**
* @brief Coleta um inteiro do vetor de referência e coloca na pilha.
* @param *curr_frame ponteiro para o frame atual
* @return void
*/
void iaload(Frame *curr_frame) {
  if (DEBUG) cout << "----------iaload----------\n";
  Operand* index = curr_frame->pop_operand();
  Operand* array = curr_frame->pop_operand();

  if (DEBUG) cout << "array size: " << array->array_type->array->size() << "\n";
  Operand* op = array->array_type->array->at(index->type_int);

  if (DEBUG) cout << "array index: " << (int)index->type_int << "\n";

  for (int j=0; (unsigned)j < array->array_type->array->size(); ++j) {
    int value = (array->array_type->array->at(j))->type_int;
    if (DEBUG) cout << "array item: " << value << "\n";
  }

  curr_frame->push_operand(op);
  curr_frame->pc++;
}

/**
* @brief Coleta um long do vetor de referência e coloca na pilha.
* @param *curr_frame ponteiro para o frame atual
* @return void
*/
void laload(Frame *curr_frame) {
  if (DEBUG) cout << "----------laload----------\n";
  Operand* index = curr_frame->pop_operand();
  Operand* array = curr_frame->pop_operand();

  if (DEBUG) cout << "array size: " << array->array_type->array->size() << "\n";
  Operand* op = array->array_type->array->at(index->type_int);
  if (DEBUG) cout << "array index: " << (int)index->type_int << "\n";

  for (int j=0; (unsigned)j < array->array_type->array->size(); ++j) {
    int value = (array->array_type->array->at(j))->type_long;
    if (DEBUG) cout << "array item: " << value << "\n";
  }

  curr_frame->push_operand(op);
  curr_frame->pc++;
}

/**
* @brief Coleta um float do vetor de referência e coloca na pilha.
* @param *curr_frame ponteiro para o frame atual
* @return void
*/
void faload(Frame *curr_frame) {
  if (DEBUG) cout << "----------faload----------\n";
  Operand* index = curr_frame->pop_operand();
  Operand* array = curr_frame->pop_operand();

  if (DEBUG) cout << "array size: " << array->array_type->array->size() << "\n";
  Operand* op = array->array_type->array->at(index->type_int);

  if (DEBUG) cout << "array index: " << (int)index->type_int << "\n";
  if (DEBUG) cout << "array index value: " << op->type_float << "\n";

  for (int j=0; (unsigned)j < array->array_type->array->size(); ++j) {
    int value = (array->array_type->array->at(j))->type_float;
    if (DEBUG) cout << "array item : " << value << "\n";
  }

  curr_frame->push_operand(op);
  curr_frame->pc++;
}

/**
* @brief Coleta um double do vetor de referência e coloca na pilha.
* @param *curr_frame ponteiro para o frame atual
* @return void
*/
void daload(Frame *curr_frame) {
  if (DEBUG) cout << "----------daload----------\n";
  Operand* index = curr_frame->pop_operand();
  Operand* array = curr_frame->pop_operand();

  if (DEBUG) cout << "array size: " << array->array_type->array->size() << "\n";
  Operand* op = array->array_type->array->at(index->type_int);
  if (DEBUG) cout << "array index: " << (int)index->type_int << "\n";
  for (int j=0; (unsigned)j < array->array_type->array->size(); ++j) {
    int value = (array->array_type->array->at(j))->type_double;
    if (DEBUG) cout << "array item : " << value << "\n";
  }

  curr_frame->push_operand(op);
  curr_frame->pc++;
}

/**
* @brief Coleta um objeto do vetor de referência e coloca na pilha.
* @param *curr_frame ponteiro para o frame atual
* @return void
*/
void aaload(Frame *curr_frame) {
  if (DEBUG) cout << "----------aaload----------\n";
  Operand* index = curr_frame->pop_operand();
  Operand* array = curr_frame->pop_operand();

  if (DEBUG) cout << "array size : " << array->array_type->array->size() << "\n";
  Operand* op = array->array_type->array->at(index->type_int);
  if (DEBUG) cout << "array index : " << (int)index->type_int << "\n";

  for (int j=0; (unsigned)j < array->array_type->array->size(); ++j) {
    if (DEBUG) cout << "sub array size : " << (array->array_type->array->at(j))->array_type->array->size() << "\n";
  }

  curr_frame->push_operand(op);
  curr_frame->pc++;
}

/**
* @brief Coleta um booleano do vetor de referência e coloca na pilha.
* @param *curr_frame ponteiro para o frame atual
* @return void
*/
void baload(Frame *curr_frame) {
  if (DEBUG) cout << "----------baload----------\n";
  Operand* index = curr_frame->pop_operand();
  Operand* array = curr_frame->pop_operand();

  if (DEBUG) cout << "array size: " << array->array_type->array->size() << "\n";
  Operand* op = array->array_type->array->at(index->type_int);
  if (DEBUG) cout << "array index: " << (int)index->type_int << "\n";

  for (int j=0; (unsigned)j < array->array_type->array->size(); ++j) {
    int value = (array->array_type->array->at(j))->type_bool;
    if (DEBUG) cout << "array item: " << value << "\n";
  }
  
  curr_frame->push_operand(op);
  curr_frame->pc++;
}

/**
* @brief Coleta um char do vetor de referência e coloca na pilha.
* @param *curr_frame ponteiro para o frame atual
* @return void
*/
void caload(Frame *curr_frame) {
  if (DEBUG) cout << "----------caload----------\n";
  Operand* index = curr_frame->pop_operand();
  Operand* array = curr_frame->pop_operand();

  if (DEBUG) cout << "array size: " << array->array_type->array->size() << "\n";
  Operand* op = array->array_type->array->at(index->type_int);
  if (DEBUG) cout << "array index: " << (int)index->type_int << "\n";

  for (int j=0; (unsigned)j < array->array_type->array->size(); ++j) {
    int value = (array->array_type->array->at(j))->type_char;
    if (DEBUG) cout << "array item: " << value << "\n";
  }

  curr_frame->push_operand(op);
  curr_frame->pc++;
}

/**
* @brief Coleta um char do vetor de referência e coloca na pilha.
* @param *curr_frame ponteiro para o frame atual
* @return void
*/
void saload(Frame *curr_frame) {
  if (DEBUG) cout << "----------saload----------\n";
  Operand* index = curr_frame->pop_operand();
  Operand* array = curr_frame->pop_operand();

  if (DEBUG) cout << "array size: " << array->array_type->array->size() << "\n";
  Operand* op = array->array_type->array->at(index->type_int);
  if (DEBUG) cout << "array index: " << (int)index->type_int << "\n";

  for (int j=0; (unsigned)j < array->array_type->array->size(); ++j) {
    int value = (array->array_type->array->at(j))->type_short;
    if (DEBUG) cout << "array item: " << value << "\n";
  }

  curr_frame->push_operand(op);
  curr_frame->pc++;
}

