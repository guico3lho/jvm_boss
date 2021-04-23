/** @file instructions_conversions.cpp
 *  @brief Módulo que contém as instruções de opcode do tipo conversion da JVM.
*/

#include "interpreter.hpp"

/*************************** CONVERSIONS ***************************/

/**
 * @brief Resgata o valor do topo da pilha (que deve ser int), covnerte para
 *  long e salva na pilha de operandos
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void i2l(Frame *curr_frame) {
  if (DEBUG) cout << "----------i2l----------\n";

    int value_op;
    Operand *op_int = curr_frame->pop_operand();
    memcpy(&value_op, &op_int->type_int, sizeof(u4));

    long value_long = (long)value_op;
    Operand *value_converted = check_string_create_type("J");
    memcpy(&value_converted->type_long, &value_long, sizeof(u8));

    curr_frame->pc++;
    curr_frame->push_operand(value_converted);
    if (DEBUG) cout << "i2l\n";
}

/**
* @brief Converte de inteiro para float
* @param *curr_frame ponteiro para o frame atual
* @return void
*/
void i2f(Frame *curr_frame) {
  if (DEBUG) cout << "----------i2f----------\n";

  int stack_value;
  Operand *operand = curr_frame->pop_operand();
  memcpy(&stack_value, &operand->type_int, sizeof(u4));

  float converted_value = (float) stack_value;
  Operand *float_converted_type = check_string_create_type("F");
  memcpy(&float_converted_type->type_float, &converted_value, sizeof(u4));

  curr_frame->pc++;
  curr_frame->push_operand(float_converted_type);
}

/**
 * @brief Converte de int para double
 * @param *curr_frame ponteiro que aponta para o frame atual
 * @return void
 */
void i2d(Frame *curr_frame) {
  if (DEBUG) cout << "----------i2d----------\n";

  int stack_value;
  Operand *int_type = curr_frame->pop_operand();
  stack_value = int_type->type_int;
  if (DEBUG) cout << "i2d int value " << stack_value << "\n";

  double d_value_cast = (double)stack_value;
  if (DEBUG) cout << "i2d double value " << d_value_cast << "\n";
  Operand *d_value_cast_type = check_string_create_type("D");
  memcpy(&d_value_cast_type->type_double, &d_value_cast, sizeof(u8));

  curr_frame->pc++;
  curr_frame->push_operand(d_value_cast_type);

  if (DEBUG) cout << "i2d\n";
}

/**
 * @brief Converte int para byte.
 * @param *curr_frame ponteiro que aponta para o frame atual
 * @return void
 */
void i2b(Frame *curr_frame) {
  if (DEBUG) cout << "----------i2b----------\n";
  curr_frame->pc++;

  int stack_value;
  Operand *int_type = curr_frame->pop_operand();
  memcpy(&stack_value, &int_type->type_int, sizeof(u4));

  u4 conv_value = (u4) stack_value;
  Operand *op_from_type = check_string_create_type("B");
  memcpy(&op_from_type->type_byte, &conv_value, sizeof(u4));

  curr_frame->push_operand(op_from_type);
}

/**
 * @brief Converte int para short int.
 * @param *curr_frame ponteiro que aponta para o frame atual
 * @return void
 */
void i2s(Frame *curr_frame) {
  if (DEBUG) cout << "----------i2s----------\n";

  curr_frame->pc++;

  int stack_value;
  Operand *int_type = curr_frame->pop_operand();
  memcpy(&stack_value, &int_type->type_int, sizeof(u4));

  short conv_value = (short)stack_value;
  Operand *op_from_type = check_string_create_type("S");
  memcpy(&op_from_type->type_byte, &conv_value, sizeof(u4));

  curr_frame->push_operand(op_from_type);

  if (DEBUG) cout << "i2s\n";
}

/**
 * @brief Converte um long para int
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void l2i(Frame *curr_frame) {
  if (DEBUG) cout << "----------l2i----------\n";

  long stack_value;
  Operand *long_type = curr_frame->pop_operand();
  memcpy(&stack_value, &long_type->type_long, sizeof(u8));

  int new_value = (int) stack_value;
  Operand *new_int = check_string_create_type("I");
  memcpy(&new_int->type_int, &new_value, sizeof(u4));

  curr_frame->push_operand(new_int);
  curr_frame->pc++;
}

/**
* @brief Converte de long para float
* @param *curr_frame ponteiro para o frame atual
* @return void
*/
void l2f(Frame *curr_frame) {
  if (DEBUG) cout << "----------l2f----------\n";

  long stack_value;
  Operand *operand = curr_frame->pop_operand();
  memcpy(&stack_value, &operand->type_long, sizeof(u8));

  float converted_value = (float) stack_value;
  Operand *float_converted_type = check_string_create_type("F");
  memcpy(&float_converted_type->type_float, &converted_value, sizeof(u4));

  curr_frame->pc++;
  curr_frame->push_operand(float_converted_type);
}

/**
 * @brief Converte um long para double
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void l2d(Frame *curr_frame) {
  if (DEBUG) cout << "----------l2d----------\n";

  long stack_value;
  Operand *long_type = curr_frame->pop_operand();
  memcpy(&stack_value, &long_type->type_long, sizeof(u8));

  double new_value = (double) stack_value;
  Operand *new_double = check_string_create_type("D");
  memcpy(&new_double->type_double, &new_value, sizeof(u8));

  curr_frame->push_operand(new_double);
  curr_frame->pc++;
}

/**
 * @brief Converte de float para inteiro
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void f2i(Frame *curr_frame) {
  if (DEBUG) cout << "----------f2i----------\n";

  Operand *op = curr_frame->pop_operand();
  u4 float_bits = op->type_float;
  if (DEBUG) cout << "f2i float_bits: " << float_bits << "\n";

  float float_value = float_bits_to_value(float_bits);
  if (DEBUG) cout << "f2i float_value: " << float_value << "\n";

  int int_value = (int) float_value;
  Operand *new_int = check_string_create_type("I");
  memcpy(&new_int->type_int, &int_value, sizeof(u4));
  if (DEBUG) cout << "f2i int " << int_value << "\n";

  curr_frame->push_operand(new_int);
  curr_frame->pc++;
}

void f2l(Frame *curr_frame) {
  if (DEBUG) cout << "----------f2l----------\n";

  Operand *op = curr_frame->pop_operand();
  u4 float_bits = op->type_float;
  if (DEBUG) cout << "f2l float_bits: " << float_bits << "\n";

  float float_value = float_bits_to_value(float_bits);
  if (DEBUG) cout << "f2l float_value: " << float_value << "\n";

  long conv_value = (long) float_value;
  Operand *longConvertidoType = check_string_create_type("J");
  memcpy(&longConvertidoType->type_long, &conv_value, sizeof(uint64_t));
  if (DEBUG) cout << "f2l long value " << longConvertidoType->type_long << "\n";

  curr_frame->pc++;
  curr_frame->push_operand(longConvertidoType);
}

/**
 * @brief Converte de float para double
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void f2d(Frame *curr_frame) {
  if (DEBUG) cout << "----------f2d----------\n";
  curr_frame->pc++;

  Operand *op = curr_frame->pop_operand();
  u4 float_bits = op->type_float;
  if (DEBUG) cout << "f2d float_bits: " << float_bits << "\n";

  float float_value = float_bits_to_value(float_bits);
  if (DEBUG) cout << "f2d float_value: " << float_value << "\n";

  double double_value = (double) float_value;
  if (DEBUG) cout << "f2d double value " << double_value << "\n";
  Operand *new_double = check_string_create_type("D");
  memcpy(&new_double->type_double, &double_value, sizeof(u8));

  curr_frame->push_operand(new_double);
}

/**
 * @brief Converte de double para int
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void d2i(Frame *curr_frame) {
  if (DEBUG) cout << "----------d2i----------\n";

  double stack_value;
  Operand *double_type = curr_frame->pop_operand();
  memcpy(&stack_value, &double_type->type_double, sizeof(int64_t));

  if (DEBUG) cout << "d2i double value : " << stack_value << "\n";

  int int_value = (int)stack_value;
  Operand *new_int = check_string_create_type("I");
  memcpy(&new_int->type_int, &int_value, sizeof(u4));

  if (DEBUG) cout << "d2i int value : " << new_int->type_int << "\n";

  curr_frame->push_operand(new_int);
  curr_frame->pc++;
}

/**
 * @brief Converte de double para long
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void d2l(Frame *curr_frame) {
  if (DEBUG) cout << "----------d2l----------\n";

  double stack_value;
  Operand *double_type = curr_frame->pop_operand();
  memcpy(&stack_value, &double_type->type_double, sizeof(int64_t));

  long long_value = (long)stack_value;
  Operand *new_long = check_string_create_type("J");
  memcpy(&new_long->type_long, &long_value, sizeof(u8));

  curr_frame->push_operand(new_long);
  curr_frame->pc++;
}

/**
 * @brief Converte double para float
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void d2f(Frame *curr_frame) {
  if (DEBUG) cout << "----------d2f----------\n";

  u8 stack_value;
  Operand *double_type = curr_frame->pop_operand();
  memcpy(&stack_value, &double_type->type_double, sizeof(u8));
  if (DEBUG) cout << "d2f double value : " << stack_value << "\n";

  float float_value = (float) stack_value;
  Operand *new_float = check_string_create_type("F");
  memcpy(&new_float->type_float, &float_value, sizeof(u4));
  if (DEBUG) cout << "d2f float value : " << new_float->type_float << "\n";

  curr_frame->push_operand(new_float);
  curr_frame->pc++;
}


