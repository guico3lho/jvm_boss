/** @file instructions_conversions.cpp
 *  @brief Módulo que contém as instruções de opcode do tipo conversion da JVM.
*/

#include "interpreter.hpp"

/*************************** CONVERSIONS ***************************/

/**
 * @brief Converte de int para long
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void i2l(Frame *curr_frame) {
  if (DEBUG) cout << "----------i2l----------\n";

  int int_value;
  Operand *op_int = curr_frame->pop_operand();
  memcpy(&int_value, &op_int->type_int, sizeof (int));

  long new_value = (long) int_value;
  Operand *new_long = check_string_create_type("J");
  memcpy(&new_long->type_long, &new_value, sizeof (long));

  curr_frame->pc++;
  curr_frame->push_operand(new_long);
}

/**
* @brief Converte de int para float
* @param *curr_frame ponteiro para o frame atual
* @return void
*/
void i2f(Frame *curr_frame) {
  if (DEBUG) cout << "----------i2f----------\n";

  int int_value;
  Operand *op_int = curr_frame->pop_operand();
  memcpy(&int_value, &op_int->type_int, sizeof (int));

  float new_value = (float) int_value;
  Operand *new_float = check_string_create_type("F");
  memcpy(&new_float->type_float, &new_value, sizeof (float));

  curr_frame->pc++;
  curr_frame->push_operand(new_float);
}

/**
 * @brief Converte de int para double
 * @param *curr_frame ponteiro que aponta para o frame atual
 * @return void
 */
void i2d(Frame *curr_frame) {
  if (DEBUG) cout << "----------i2d----------\n";

  int int_value;
  Operand *op_int = curr_frame->pop_operand();
  int_value = op_int->type_int;
  if (DEBUG) cout << "i2d int value " << int_value << "\n";

  double new_value = (double) int_value;
  if (DEBUG) cout << "i2d double value " << new_value << "\n";
  Operand *new_double = check_string_create_type("D");
  memcpy(&new_double->type_double, &new_value, sizeof (double));

  curr_frame->pc++;
  curr_frame->push_operand(new_double);
}

/**
 * @brief Converte int para byte.
 * @param *curr_frame ponteiro que aponta para o frame atual
 * @return void
 */
void i2b(Frame *curr_frame) {
  if (DEBUG) cout << "----------i2b----------\n";
  curr_frame->pc++;

  int int_value;
  Operand *op_int = curr_frame->pop_operand();
  memcpy(&int_value, &op_int->type_int, sizeof (int));

  u4 new_value = (u4) int_value;
  Operand *new_byte = check_string_create_type("B");
  memcpy(&new_byte->type_byte, &new_value, sizeof (u4));

  curr_frame->push_operand(new_byte);
}

/**
 * @brief Converte int para char.
 * @param *curr_frame ponteiro que aponta para o frame atual
 * @return void
 */
void i2c(Frame *curr_frame) {
  if (DEBUG) cout << "----------i2c----------\n";
  curr_frame->pc++;

  int int_value;
  Operand *op_int = curr_frame->pop_operand();
  memcpy(&int_value, &op_int->type_int, sizeof (int));

  char new_value = (char) int_value;
  Operand *new_char = check_string_create_type("C");
  memcpy(&new_char->type_byte, &new_value, sizeof (char));

  curr_frame->push_operand(new_char);
}

/**
 * @brief Converte int para short int.
 * @param *curr_frame ponteiro que aponta para o frame atual
 * @return void
 */
void i2s(Frame *curr_frame) {
  if (DEBUG) cout << "----------i2s----------\n";
  curr_frame->pc++;

  int int_value;
  Operand *op_int = curr_frame->pop_operand();
  memcpy(&int_value, &op_int->type_int, sizeof (int));

  short new_value = (short) int_value;
  Operand *new_short = check_string_create_type("S");
  memcpy(&new_short->type_byte, &new_value, sizeof (short));

  curr_frame->push_operand(new_short);
}

/**
 * @brief Converte de long para int
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void l2i(Frame *curr_frame) {
  if (DEBUG) cout << "----------l2i----------\n";

  long long_value;
  Operand *op_long = curr_frame->pop_operand();
  memcpy(&long_value, &op_long->type_long, sizeof (long));

  int new_value = (int) long_value;
  Operand *new_int = check_string_create_type("I");
  memcpy(&new_int->type_int, &new_value, sizeof (int));

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

  long long_value;
  Operand *op_long = curr_frame->pop_operand();
  memcpy(&long_value, &op_long->type_long, sizeof (long));

  float new_value = (float) long_value;
  Operand *new_float = check_string_create_type("F");
  memcpy(&new_float->type_float, &new_value, sizeof (float));

  curr_frame->pc++;
  curr_frame->push_operand(new_float);
}

/**
 * @brief Converte de long para double
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void l2d(Frame *curr_frame) {
  if (DEBUG) cout << "----------l2d----------\n";

  long long_value;
  Operand *op_long = curr_frame->pop_operand();
  memcpy(&long_value, &op_long->type_long, sizeof (long));

  double new_value = (double) long_value;
  Operand *new_double = check_string_create_type("D");
  memcpy(&new_double->type_double, &new_value, sizeof (double));

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

  Operand *op_float = curr_frame->pop_operand();
  u4 float_bits = op_float->type_float;
  if (DEBUG) cout << "f2i float_bits: " << float_bits << "\n";

  float float_value = float_bits_to_value(float_bits);
  if (DEBUG) cout << "f2i float_value: " << float_value << "\n";

  int int_value = (int) float_value;
  Operand *new_int = check_string_create_type("I");
  memcpy(&new_int->type_int, &int_value, sizeof (int));
  if (DEBUG) cout << "f2i int " << int_value << "\n";

  curr_frame->push_operand(new_int);
  curr_frame->pc++;
}

/**
 * @brief Converte de float para long
 * 
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void f2l(Frame *curr_frame) {
  if (DEBUG) cout << "----------f2l----------\n";

  Operand *op_float = curr_frame->pop_operand();
  u4 float_bits = op_float->type_float;
  if (DEBUG) cout << "f2l float_bits: " << float_bits << "\n";

  float float_value = float_bits_to_value(float_bits);
  if (DEBUG) cout << "f2l float_value: " << float_value << "\n";

  long new_value = (long) float_value;
  Operand *new_long = check_string_create_type("J");
  memcpy(&new_long->type_long, &new_value, sizeof (long));
  if (DEBUG) cout << "f2l long value " << new_long->type_long << "\n";

  curr_frame->pc++;
  curr_frame->push_operand(new_long);
}

/**
 * @brief Converte de float para double
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void f2d(Frame *curr_frame) {
  if (DEBUG) cout << "----------f2d----------\n";
  curr_frame->pc++;

  Operand *op_float = curr_frame->pop_operand();
  u4 float_bits = op_float->type_float;
  if (DEBUG) cout << "f2d float_bits: " << float_bits << "\n";

  float float_value = float_bits_to_value(float_bits);
  if (DEBUG) cout << "f2d float_value: " << float_value << "\n";

  double double_value = (double) float_value;
  if (DEBUG) cout << "f2d double value " << double_value << "\n";
  Operand *new_double = check_string_create_type("D");
  memcpy(&new_double->type_double, &double_value, sizeof (double));

  curr_frame->push_operand(new_double);
}

/**
 * @brief Converte de double para int
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void d2i(Frame *curr_frame) {
  if (DEBUG) cout << "----------d2i----------\n";

  double double_value;
  Operand *double_type = curr_frame->pop_operand();
  memcpy(&double_value, &double_type->type_double, sizeof (double));
  if (DEBUG) cout << "d2i double value : " << double_value << "\n";

  int int_value = (int) double_value;
  Operand *new_int = check_string_create_type("I");
  memcpy(&new_int->type_int, &int_value, sizeof (int));
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

  double double_value;
  Operand *double_type = curr_frame->pop_operand();
  memcpy(&double_value, &double_type->type_double, sizeof(u8));

  long long_value = (long) double_value;
  Operand *new_long = check_string_create_type("J");
  memcpy(&new_long->type_long, &long_value, sizeof(long));

  curr_frame->push_operand(new_long);
  curr_frame->pc++;
}

/**
 * @brief Converte de double para float
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void d2f(Frame *curr_frame) {
  if (DEBUG) cout << "----------d2f----------\n";

  Operand *op = curr_frame->pop_operand();
  u8 double_bits = op->type_double;
  if (DEBUG) cout << "d2f double_bits: " << double_bits << "\n";

  double double_value = double_bits_to_value(double_bits);
  if (DEBUG) cout << "d2f double_value: " << double_value << "\n";

  float float_value = (float) double_value;
  Operand *new_float = check_string_create_type("F");
  memcpy(&new_float->type_float, &float_value, sizeof(float));
  if (DEBUG) cout << "d2f float value : " << new_float->type_float << "\n";

  curr_frame->push_operand(new_float);
  curr_frame->pc++;
}


