/** @file instructions_control.cpp
 *  @brief Módulo que contém as instruções de opcode do tipo controle da JVM.
*/

#include "interpreter.hpp"

/*************************** CONTROL ***************************/

/**
 * @brief Função para saltar para um certo offset.
 * @param curr_frame ponteiro para o frame atual
 * @return void
 */
void ins_goto(Frame* curr_frame) {
  if (DEBUG) cout << "----------goto----------\n";
  int16_t offset = curr_frame->method_code->code[curr_frame->pc + 1];
  offset = (offset << 8) + curr_frame->method_code->code[curr_frame->pc + 2];
  curr_frame->pc += offset;
}

void ret(Frame* curr_frame) {
  u1 index = curr_frame->method_code->code[curr_frame->pc + 1];
  curr_frame->pc = curr_frame->local_variables_array[index]->type_int;
}

/**
 * @brief Acessa tabela de jumps por chave e realizar jump.
 * @param Frame* curr_frame ponteiro que aponta para o frame atual
 * @return void
 */
void tableswitch(Frame* curr_frame){
  if (DEBUG) cout << "----------tableswitch----------\n";
  u4 default_byte = 0;
  u4 low_byte = 0;
  u4 hight_byte = 0;
  u4 *jump_table;
  u4 index;

  u4 start_pc = curr_frame->pc;
  curr_frame->pc++;

  while (curr_frame->pc % 4 != 0) curr_frame->pc++;
  
  default_byte = curr_frame->method_code->code[curr_frame->pc++];
  for (int i = 0; i < 3; i++) 
    default_byte = (default_byte << 8) + curr_frame->method_code->code[curr_frame->pc++];
  
  low_byte = curr_frame->method_code->code[curr_frame->pc++];
  for (int i = 0; i < 3; i++) 
    low_byte = (low_byte << 8) + curr_frame->method_code->code[curr_frame->pc++];
  
  hight_byte = curr_frame->method_code->code[curr_frame->pc++];
  for (int i = 0; i < 3; i++) 
    hight_byte = (hight_byte << 8) + curr_frame->method_code->code[curr_frame->pc++];
  
  jump_table = (u4*) malloc((hight_byte - low_byte + 1) * sizeof(u4));

  for (int i = 0; i < (int) (hight_byte - low_byte + 1); i++) {

    jump_table[i] = curr_frame->method_code->code[curr_frame->pc++];
    for (int j = 0; j < 3; j++) 
      jump_table[i] = (jump_table[i] << 8) + curr_frame->method_code->code[curr_frame->pc++];
  }

  Operand* op1 = curr_frame->pop_operand();
  index = op1->type_int;

  if ((int32_t) index < (int32_t) low_byte || (int32_t) index > (int32_t) hight_byte) {
    curr_frame->pc = start_pc + (int32_t) default_byte;
  } else {
    curr_frame->pc = start_pc + (int32_t) jump_table[index - low_byte];
  }

  free(jump_table);
}

/**
 * @brief Acessa tabela de salto por chave e realiza salto.
 * @param Frame* curr_frame ponteiro que aponta para o frame atual
 * @return void
 */
void lookupswitch(Frame* curr_frame) {
  u4 default_byte = 0;
  u4 nPairs = 0;
  u4 *jump_keys;
  u4 *jump_table;
  u4 key;

  u4 start_pc = curr_frame->pc;
  curr_frame->pc++;

  while (curr_frame->pc % 4 != 0) {
    curr_frame->pc++;
  }

  default_byte = curr_frame->method_code->code[curr_frame->pc++];
  for (int i = 0; i < 3; i++) {
    default_byte = (default_byte << 8) + curr_frame->method_code->code[curr_frame->pc++];
  }

  nPairs = curr_frame->method_code->code[curr_frame->pc++];
  for (int i = 0; i < 3; i++) 
    nPairs = (nPairs << 8) + curr_frame->method_code->code[curr_frame->pc++];

  jump_keys = (u4*) malloc(nPairs * sizeof(u4));
  jump_table = (u4*) malloc(nPairs * sizeof(u4));

  for (int i = 0; i < (int) nPairs; i++) {

    jump_keys[i] = curr_frame->method_code->code[curr_frame->pc++];
    for (int j = 0; j < 3; j++) 
      jump_keys[i] = (jump_keys[i] << 8) + curr_frame->method_code->code[curr_frame->pc++];
    
    jump_table[i] = curr_frame->method_code->code[curr_frame->pc++];
    for (int j = 0; j < 3; j++) 
      jump_table[i] = (jump_table[i] << 8) + curr_frame->method_code->code[curr_frame->pc++];
  }

  Operand* op1 = curr_frame->pop_operand();
  key = op1->type_int;

  int match;
  for (match = 0; match < (int) nPairs; ++match) {
    if (jump_keys[match] == key) {
      curr_frame->pc = start_pc + jump_table[match];
      break;
    }
  }

  if ((unsigned) match == nPairs)
    curr_frame->pc = start_pc + default_byte;

  free(jump_keys);
  free(jump_table);
}

/**
 * @brief Retorna int de um método.
 * @param curr_frame ponteiro para o frame atual
 * @return void
 */
void ireturn(Frame* curr_frame) {
  curr_frame->pc++;
  Operand* integer = curr_frame->pop_operand();
  pop_frame();
  Frame* called_frame = top_frame();
  called_frame->push_operand(integer);
}

/**
 * @brief Retorna long int de um método.
 * @param Frame* curr_frame ponteiro que aponta para o frame atual
 * @return void
 */
void lreturn(Frame* curr_frame) {
  curr_frame->pc++;
  Operand* long_value = curr_frame->pop_operand();
  pop_frame();
  Frame* past_frame = top_frame();
  past_frame->push_operand(long_value);
}

/**
 * @brief Retorna float de um método.
 * @param Frame* curr_frame ponteiro o frame atual
 * @return void
 */
void freturn(Frame* curr_frame) {
  curr_frame->pc++;
  Operand* float_value = curr_frame->pop_operand();
  pop_frame();
  Frame* called_frame = top_frame();
  called_frame->push_operand(float_value);
}

/**
 * @brief Retorna double de um método.
 * @param curr_frame ponteiro para o frame atual
 * @return void
 */
void dreturn(Frame* curr_frame) {
  curr_frame->pc++;
  Operand* double_value = curr_frame->pop_operand();
  pop_frame();
  Frame* called_frame = top_frame();
  called_frame->push_operand(double_value);
}

/**
 * @brief Retorna objeto de um método.
 * @param curr_frame ponteiro para o frame atual
 * @return void
 */
void areturn(Frame* curr_frame) {
  curr_frame->pc++;
  Operand* object = curr_frame->pop_operand();
  pop_frame();
  Frame* called_frame = top_frame();
  called_frame->push_operand(object);
}

/**
* @brief Retorna void de uma instrução.
* @param curr_frame ponteiro para o frame atual
* @return void
*/
void void_return(Frame* curr_frame) {
  if (DEBUG) cout << "----------void_return----------\n";
  curr_frame->pc++;
  pop_frame();
}
