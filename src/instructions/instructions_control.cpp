/** @file instructions_control.cpp
 *  @brief Módulo que contém as instruções de opcode do tipo controle da JVM.
*/

#include "interpreter.hpp"

/*************************** CONTROL ***************************/

/**
 * @brief Função para saltar para um certo offset.
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void ins_goto(Frame *curr_frame) {
  if (DEBUG) cout << "----------goto----------\n";
  int16_t offset = curr_frame->method_code->code[curr_frame->pc + 1];
  offset = (offset << 8) + curr_frame->method_code->code[curr_frame->pc + 2];
  curr_frame->pc += offset;
}

void ret(Frame *curr_frame) {
  u1 index = curr_frame->method_code->code[curr_frame->pc + 1];
  curr_frame->pc = curr_frame->local_variables_array[index]->type_int;
}

/**
 * @brief Acessa tabela de salto por chave e realizar salto.
 * @param Frame *curr_frame ponteiro que aponta para o frame atual
 * @return void
 */
void tableswitch(Frame *curr_frame){
  if (DEBUG) cout << "----------tableswitch----------\n";
  u4 dftByte = 0;
  u4 byteL = 0;
  u4 byteH = 0;
  u4 *jpOffset;
  u4 index;
  Operand *value1 = curr_frame->pop_operand();
  index = value1->type_int;
  u4 strt = curr_frame->pc;
  curr_frame->pc++;

  while (curr_frame->pc % 4 != 0) {
    curr_frame->pc++;
  }

  dftByte = curr_frame->method_code->code[curr_frame->pc++];
  dftByte = (dftByte << 8) + curr_frame->method_code->code[curr_frame->pc++];
  dftByte = (dftByte << 8) + curr_frame->method_code->code[curr_frame->pc++];
  dftByte = (dftByte << 8) + curr_frame->method_code->code[curr_frame->pc++];

  byteL = curr_frame->method_code->code[curr_frame->pc++];
  byteL = (byteL << 8) + curr_frame->method_code->code[curr_frame->pc++];
  byteL = (byteL << 8) + curr_frame->method_code->code[curr_frame->pc++];
  byteL = (byteL << 8) + curr_frame->method_code->code[curr_frame->pc++];

  byteH = curr_frame->method_code->code[curr_frame->pc++];
  byteH = (byteH << 8) + curr_frame->method_code->code[curr_frame->pc++];
  byteH = (byteH << 8) + curr_frame->method_code->code[curr_frame->pc++];
  byteH = (byteH << 8) + curr_frame->method_code->code[curr_frame->pc++];

  jpOffset = (u4*)malloc((byteH - byteL + 1) * sizeof(u4));

  for (int i = 0; i < (int)(byteH - byteL + 1); i++) {
    jpOffset[i] = curr_frame->method_code->code[curr_frame->pc++];
    jpOffset[i] = (jpOffset[i] << 8) + curr_frame->method_code->code[curr_frame->pc++];
    jpOffset[i] = (jpOffset[i] << 8) + curr_frame->method_code->code[curr_frame->pc++];
    jpOffset[i] = (jpOffset[i] << 8) + curr_frame->method_code->code[curr_frame->pc++];
  }

  if ((int32_t)index < (int32_t)byteL || (int32_t)index >(int32_t)byteH) {
    curr_frame->pc = strt + (int32_t)dftByte;
  }
  else {
    curr_frame->pc = strt + (int32_t)jpOffset[index - byteL];
  }

  free(jpOffset);
}

/**
 * @brief Acessa tabela de salto por chave e realiza salto.
 * @param Frame *curr_frame ponteiro que aponta para o frame atual
 * @return void
 */
void lookupswitch(Frame *curr_frame) {
  u4 dftByte = 0;
  u4 nPares = 0;
  u4 *jpKeys;
  u4 *jpOffset;
  u4 key;
  u4 start = curr_frame->pc;

  Operand *value_1 = curr_frame->pop_operand();
  key = value_1->type_int;
  curr_frame->pc++;

  while (curr_frame->pc % 4 != 0) {
    curr_frame->pc++;
  }

  dftByte = curr_frame->method_code->code[curr_frame->pc++];
  dftByte = (dftByte << 8) + curr_frame->method_code->code[curr_frame->pc++];
  dftByte = (dftByte << 8) + curr_frame->method_code->code[curr_frame->pc++];
  dftByte = (dftByte << 8) + curr_frame->method_code->code[curr_frame->pc++];

  nPares = curr_frame->method_code->code[curr_frame->pc++];
  nPares = (nPares << 8) + curr_frame->method_code->code[curr_frame->pc++];
  nPares = (nPares << 8) + curr_frame->method_code->code[curr_frame->pc++];
  nPares = (nPares << 8) + curr_frame->method_code->code[curr_frame->pc++];

  jpKeys = (u4*)malloc(nPares * sizeof(u4));
  jpOffset = (u4*)malloc(nPares * sizeof(u4));
  for (int i = 0; i < (int)nPares; i++) {
    jpKeys[i] = curr_frame->method_code->code[curr_frame->pc++];
    jpKeys[i] = (jpKeys[i] << 8) + curr_frame->method_code->code[curr_frame->pc++];
    jpKeys[i] = (jpKeys[i] << 8) + curr_frame->method_code->code[curr_frame->pc++];
    jpKeys[i] = (jpKeys[i] << 8) + curr_frame->method_code->code[curr_frame->pc++];

    jpOffset[i] = curr_frame->method_code->code[curr_frame->pc++];
    jpOffset[i] = (jpOffset[i] << 8) + curr_frame->method_code->code[curr_frame->pc++];
    jpOffset[i] = (jpOffset[i] << 8) + curr_frame->method_code->code[curr_frame->pc++];
    jpOffset[i] = (jpOffset[i] << 8) + curr_frame->method_code->code[curr_frame->pc++];
  }

  int i;
  for (i = 0; i < (int)nPares; ++i) {
    if (jpKeys[i] == key) {
      curr_frame->pc = start + jpOffset[i];
      break;
    }
  }
  if ((unsigned)i == nPares)
    curr_frame->pc = start + dftByte;

  free(jpKeys);
  free(jpOffset);
}

/**
 * @brief Retorna int de um método.
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void ireturn(Frame *curr_frame) {
  curr_frame->pc++;
  Operand *integer = curr_frame->pop_operand();
  pop_frame();
  Frame *called_frame = top_frame();
  called_frame->push_operand(integer);
}

/**
 * @brief Retorna long int de um método.
 * @param Frame *curr_frame ponteiro que aponta para o frame atual
 * @return void
 */
void lreturn(Frame *curr_frame) {
  curr_frame->pc++;
  Operand *long_value = curr_frame->pop_operand();
  pop_frame();
  Frame *past_frame = top_frame();
  past_frame->push_operand(long_value);
}

/**
 * @brief Retorna float de um método.
 * @param Frame *curr_frame ponteiro o frame atual
 * @return void
 */
void freturn(Frame *curr_frame) {
  curr_frame->pc++;
  Operand *float_value = curr_frame->pop_operand();
  pop_frame();
  Frame *called_frame = top_frame();
  called_frame->push_operand(float_value);
}

/**
 * @brief Retorna double de um método.
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void dreturn(Frame *curr_frame) {
  curr_frame->pc++;
  Operand *double_value = curr_frame->pop_operand();
  pop_frame();
  Frame *called_frame = top_frame();
  called_frame->push_operand(double_value);
}

/**
 * @brief Retorna objeto de um método.
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void areturn(Frame *curr_frame) {
  curr_frame->pc++;
  Operand *object = curr_frame->pop_operand();
  pop_frame();
  Frame *called_frame = top_frame();
  called_frame->push_operand(object);
}

/**
* @brief Retorna void de uma instrução.
* @param *curr_frame ponteiro para o frame atual
* @return void
*/
void void_return(Frame *curr_frame) {
  if (DEBUG) cout << "----------void_return----------\n";
  curr_frame->pc++;
  pop_frame();
}
