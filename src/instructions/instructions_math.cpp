/** @file instructions_math.cpp
 *  @brief Módulo que contém as instruções de opcode do tipo math da JVM.
*/

#include "interpreter.hpp"


/*************************** MATH ***************************/

/**
 * @brief Soma de inteiros. Retira os dois operando do topo da pilha, soma-os e coloca o resultado
 * no topo da pilha.
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void iadd(Frame* curr_frame) {
  if (DEBUG) cout << "----------iadd----------\n";

  curr_frame->pc++;

  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  Operand* result = (Operand* ) malloc(sizeof(Operand));

  result->tag = CONSTANT_INT;
  result->type_int = operand_1->type_int + operand_2->type_int;

  curr_frame->push_operand(result);

  if (DEBUG) cout << "iadd\n";
}

/**
 * @brief Soma do tipo long. Retira os dois operando do topo da pilha, soma-os e coloca o resultado
 * no topo da pilha
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void ladd(Frame* curr_frame) {
  if (DEBUG) cout << "----------ladd----------\n";

  curr_frame->pc++;
  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  Operand* result = (Operand* ) malloc(sizeof(Operand));
  result->tag = CONSTANT_LONG;
  result->type_long = operand_1->type_long + operand_2->type_long;

  curr_frame->push_operand(result);
  if (DEBUG) cout << "ladd\n";

}

/**
 * @brief Soma do tipo float. Retira os dois operando do topo da pilha, soma-os e coloca o resultado
 * no topo da pilha
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void fadd(Frame* curr_frame) {
  if (DEBUG) cout << "----------fadd----------\n";

  curr_frame->pc++;

  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  float value_1, value_2;
  memcpy(&value_1, &operand_1->type_float, sizeof(float));
  memcpy(&value_2, &operand_2->type_float, sizeof(float));
  value_1 += value_2;

  Operand* result = (Operand* ) malloc(sizeof(Operand));
  result->tag = CONSTANT_FLOAT;
  memcpy(&result->type_float, &value_1, sizeof(u4));

  curr_frame->push_operand(result);

  if (DEBUG) cout << "fadd\n";
}

/**
 * @brief Soma do tipo double. Retira os dois operando do topo da pilha, soma-os e coloca o resultado
 * no topo da pilha
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
 void dadd(Frame* curr_frame) {
  if (DEBUG) cout << "----------dadd----------\n";

  curr_frame->pc++;

  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  double value_1, value_2;
  memcpy(&value_1, &operand_1->type_double, sizeof(double));
  memcpy(&value_2, &operand_2->type_double, sizeof(double));
  value_1 += value_2;
  if (DEBUG) cout << "dadd value " << value_1 << "\n";

  Operand* result = (Operand* ) malloc(sizeof(Operand));
  result->tag = CONSTANT_DOUBLE;
  memcpy(&result->type_double, &value_1, sizeof(u8));

  curr_frame->push_operand(result);

  if (DEBUG) cout << "dadd\n";
}

/**
 * @brief Subtração do tipo inteiro. Retira os dois operando do topo da pilha,
 *  subtraí-os e coloca o resultado no topo da pilha
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void isub(Frame* curr_frame) {
  if (DEBUG) cout << "----------isub----------\n";

  curr_frame->pc++;
  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  Operand* result = (Operand* ) malloc(sizeof(Operand));
  result->tag = CONSTANT_INT;
  result->type_int = operand_2->type_int - operand_1->type_int;

  curr_frame->push_operand(result);

  if (DEBUG) cout << "isub\n";
}

/**
 * @brief Subtração do tipo long. Retira os dois operando do topo da pilha, subtraí-os e coloca o
 * resultado no topo da pilha
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void lsub(Frame* curr_frame) {
  if (DEBUG) cout << "----------lsub----------\n";

  curr_frame->pc++;
  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  Operand* result = (Operand* ) malloc(sizeof(Operand));
  result->tag = CONSTANT_LONG;
  result->type_long = operand_2->type_long - operand_1->type_long;

  curr_frame->push_operand(result);
  if (DEBUG) cout << "lsub\n";

}

/**
 * @brief Subtração do tipo float. Retira os dois operando do topo da pilha, subtraí-os e coloca o
 * resultado no topo da pilha
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void fsub(Frame* curr_frame) {
  if (DEBUG) cout << "----------fsub----------\n";

  curr_frame->pc++;

  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  float value_1, value_2;
  memcpy(&value_1, &operand_1->type_float, sizeof(float));
  memcpy(&value_2, &operand_2->type_float, sizeof(float));
  value_2 -= value_1;

  Operand* result = (Operand* ) malloc(sizeof(Operand));
  result->tag = CONSTANT_FLOAT;
  memcpy(&result->type_float, &value_2, sizeof(u4));

  curr_frame->push_operand(result);

  if (DEBUG) cout << "fsub\n";
}

/**
 * @brief Subtração do tipo double. Retira os dois operando do topo da pilha,
 *  subtraí-os e coloca o resultado no topo da pilha
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void dsub(Frame* curr_frame) {
  if (DEBUG) cout << "----------dsub----------\n";

  curr_frame->pc++;

  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  double value_1, value_2;
  memcpy(&value_1, &operand_1->type_float, sizeof(double));
  memcpy(&value_2, &operand_2->type_float, sizeof(double));
  value_2 -= value_1;

  Operand* result = (Operand* ) malloc(sizeof(Operand));
  result->tag = CONSTANT_DOUBLE;
  memcpy(&result->type_double, &value_2, sizeof(u8));

  curr_frame->push_operand(result);

  if (DEBUG) cout << "dsub\n";
}

/**
 * @brief Multiplicação de inteiros. Retira os dois operando do topo da pilha,
 *  multiplica-os e coloca o resultado no topo da pilha
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void imul(Frame* curr_frame) {
  if (DEBUG) cout << "----------imul----------\n";

  curr_frame->pc++;

  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  Operand* result = (Operand* ) malloc(sizeof(Operand));
  result->tag = CONSTANT_INT;
  result->type_int = (operand_1->type_int) * (operand_2->type_int);

  curr_frame->push_operand(result);

  if (DEBUG) cout << "imul\n";
}

/**
 * @brief Multiplicação de long. Retira os dois operando do topo da pilha, multiplica-os
 * e coloca o resultado no topo da pilha
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void lmul(Frame* curr_frame) {
  if (DEBUG) cout << "----------lmul----------\n";

  curr_frame->pc++;

  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  Operand* result = (Operand* ) malloc(sizeof(Operand));
  result->tag = CONSTANT_LONG;
  result->type_long = (operand_1->type_long) * (operand_2->type_long);

  curr_frame->push_operand(result);
  if (DEBUG) cout << "lmul\n";

}

/**
 * @brief Multiplicação de float. Retira os dois operando do topo da pilha, multiplica-os
 * e coloca o resultado no topo da pilha
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void fmul(Frame* curr_frame) {
  if (DEBUG) cout << "----------fmul----------\n";

  curr_frame->pc++;

  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  float value_1, value_2;
  memcpy(&value_1, &operand_1->type_float, sizeof(float));
  memcpy(&value_2, &operand_2->type_float, sizeof(float));
  value_2 *= value_1;

  Operand* result = (Operand* ) malloc(sizeof(Operand));
  result->tag = CONSTANT_FLOAT;
  memcpy(&result->type_float, &value_2, sizeof(u4));

  curr_frame->push_operand(result);

  if (DEBUG) cout << "fmul\n";
}

/**
 * @brief Multiplicação de double. Retira os dois operando do topo da pilha,
 *  multiplica-os e coloca o resultado no topo da pilha
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void dmul(Frame* curr_frame) {
  if (DEBUG) cout << "----------dmul----------\n";

  curr_frame->pc++;

  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  double value_1, value_2;
  memcpy(&value_1, &operand_1->type_double, sizeof(double));
  memcpy(&value_2, &operand_2->type_double, sizeof(double));
  value_2 *= value_1;

  Operand* result = (Operand* ) malloc(sizeof(Operand));
  result->tag = CONSTANT_DOUBLE;
  memcpy(&result->type_double, &value_2, sizeof(u8));

  curr_frame->push_operand(result);

  if (DEBUG) cout << "dmul\n";
}

/**
 * @brief Divisão de inteiro. Retira os dois operandos do topo da pilha,
 *  divide-os e coloca o resultado no topo da pilha
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void idiv(Frame* curr_frame) {
  if (DEBUG) cout << "----------idiv----------\n";

  curr_frame->pc++;

  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  Operand* result = (Operand* ) malloc(sizeof(Operand));
  result->tag = CONSTANT_INT;
  result->type_int = (operand_2->type_int) / (operand_1->type_int);

  curr_frame->push_operand(result);

  if (DEBUG) cout << "idiv\n";
}

/**
 * @brief Divisão de long. Retira os dois operandos do topo da pilha, divide-os
 * e coloca o resultado no topo da pilha
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void ldiv(Frame* curr_frame) {
  if (DEBUG) cout << "----------ldiv----------\n";

  curr_frame->pc++;

  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  Operand* result = (Operand* ) malloc(sizeof(Operand));
  result->tag = CONSTANT_LONG;
  result->type_long = (operand_2->type_long) / (operand_1->type_long);

  curr_frame->push_operand(result);
  if (DEBUG) cout << "ldiv\n";
}

/**
 * @brief Divisão de float. Retira os dois operandos do topo da pilha, divide-os
 * e coloca o resultado no topo da pilha
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void fdiv(Frame* curr_frame) {
  if (DEBUG) cout << "----------fdiv----------\n";

  curr_frame->pc++;

  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  float value_1, value_2;
  memcpy(&value_1, &operand_1->type_float, sizeof(float));
  memcpy(&value_2, &operand_2->type_float, sizeof(float));
  value_2 /= value_1;

  Operand* result = (Operand* ) malloc(sizeof(Operand));
  result->tag = CONSTANT_FLOAT;
  memcpy(&result->type_float, &value_2, sizeof(u4));

  curr_frame->push_operand(result);
}

/**
 * @brief Divisão de double. Retira os dois operandos do topo da pilha,
 *  divide-os e coloca o resultado no topo da pilha
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void ddiv(Frame* curr_frame) {
  if (DEBUG) cout << "----------ddiv----------\n";

  curr_frame->pc++;

  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  double value_1, value_2;
  memcpy(&value_1, &operand_1->type_double, sizeof(double));
  memcpy(&value_2, &operand_2->type_double, sizeof(double));
  value_2 /= value_1;

  Operand* result = (Operand* ) malloc(sizeof(Operand));
  result->tag = CONSTANT_DOUBLE;
  memcpy(&result->type_double, &value_2, sizeof(u8));
  if (DEBUG) cout << "ddiv result : " << result->type_double << "\n";

  curr_frame->push_operand(result);

  if (DEBUG) cout << "ddiv\n";
}

/**
 * @brief Calcula o resto da divisão entre dois inteiros.
 *  Retira os dois operandos do topo da pilha, calcula o resto da divisão e
 *  coloca no topo
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void irem(Frame* curr_frame) {
  if (DEBUG) cout << "----------irem----------\n";

  curr_frame->pc++;

  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  u4 divider = operand_1->type_int;
  u4 dividend = operand_2->type_int;

  u4 i_remainder = (u4) dividend - (dividend / divider) * divider;

  Operand* result = (Operand* ) malloc(sizeof(Operand));
  result->tag = CONSTANT_INT;
  result->type_int = i_remainder;

  curr_frame->push_operand(result);

  if (DEBUG) cout << "irem\n";
}

/**
 * @brief Calcula o resto da divisão entre dois long. Retira os dois operandos do topo da pilha,
 * calcula o resto da divisão e coloca no topo
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void lrem(Frame* curr_frame) {
  if (DEBUG) cout << "----------lrem----------\n";

  curr_frame->pc++;

  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  u8 divider = operand_1->type_int;
  u8 dividend = operand_2->type_int;

  u8 l_remainder = dividend - (dividend / divider) * divider;

  Operand* result = (Operand* ) malloc(sizeof(Operand));
  result->tag = CONSTANT_LONG;
  result->type_int = l_remainder;

  curr_frame->push_operand(result);
}

/**
 * @brief Calcula o resto da divisão entre dois floats
 * @param curr_frame ponteiro para o frame atual
 * @return void
 */
void frem(Frame* curr_frame) {
  if (DEBUG) cout << "----------frem----------\n";

    float dividend, divisor, f_remainder;

    curr_frame->pc++;
    Operand* op1 = curr_frame->pop_operand();
    Operand* op2 = curr_frame->pop_operand();

    memcpy(&divisor, &op1->type_float, sizeof(float));
    memcpy(&dividend, &op2->type_float, sizeof(float));

    f_remainder = std::fmod(dividend, divisor);

    Operand* result = (Operand*)malloc(sizeof(Operand));
    result->tag = CONSTANT_FLOAT;
    memcpy(&result->type_float, &f_remainder, sizeof(u4));
    curr_frame->push_operand(result);
}

/**
 * @brief Calcula o resto da divisão entre dois double. Retira os dois
 *  operandos do topo da pilha, calcula o resto da divisão e coloca no topo
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void drem(Frame* curr_frame) {
  if (DEBUG) cout << "----------drem----------\n";

  double dividend, divisor, f_remainder;

  curr_frame->pc++;

  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  memcpy(&divisor, &operand_1->type_double, sizeof(double));
  memcpy(&dividend, &operand_2->type_double, sizeof(double));
  f_remainder = std::fmod(dividend, divisor);

  Operand* result = check_string_create_type("D");
  memcpy(&result->type_double, &f_remainder, sizeof(u8));
  curr_frame->push_operand(result);
}

/**
 * @brief Calcula o valor negativo de int. Retira o operando do topo da pilha, nega o valor do
 * operando e o salva o resultado no topo da pilha
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void ineg(Frame* curr_frame) {
  if (DEBUG) cout << "----------ineg----------\n";

  curr_frame->pc++;

  Operand* operand = curr_frame->pop_operand();
  Operand* result = check_string_create_type("I");
  result->type_int = -(u4)operand->type_int;

  curr_frame->push_operand(result);
}

/**
 * @brief Calcula o valor negativo de long. Retira o operando do topo da pilha, nega o valor do
 * operando e o salva o resultado no topo da pilha
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void lneg(Frame* curr_frame) {
  if (DEBUG) cout << "----------lneg----------\n";

  curr_frame->pc++;

  Operand* operand = curr_frame->pop_operand();
  u8 l_value = operand->type_long;
  u8 l_result = -l_value;

  Operand* result = check_string_create_type("J");
  result->type_long = l_result;

  curr_frame->push_operand(result);
}

/**
 * @brief Calcula o valor negativo de float. Retira o operando do topo da pilha, nega o valor do
 * operando e o salva o resultado no topo da pilha
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void fneg(Frame* curr_frame) {
  if (DEBUG) cout << "----------fneg----------\n";

  float f_value;

  curr_frame->pc++;

  Operand* operand = curr_frame->pop_operand();
  memcpy(&f_value, &operand->type_float, sizeof(float));
  f_value = -f_value;

  Operand* result = check_string_create_type("F");
  memcpy(&result->type_float, &f_value, sizeof(u4));

  curr_frame->push_operand(result);
}

/**
 * @brief Calcula o valor negativo de double. Retira o operando do topo da pilha, nega o valor do
 * operando e o salva o resultado no topo da pilha
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void dneg(Frame* curr_frame) {
  if (DEBUG) cout << "----------dneg----------\n";

  double d_value;
  curr_frame->pc++;

  Operand* operand = curr_frame->pop_operand();
  memcpy(&d_value, &operand->type_double, sizeof(double));
  d_value = -d_value;

  Operand* result = check_string_create_type("D");
  memcpy(&result->type_double, &d_value, sizeof(u8));

  curr_frame->push_operand(result);
}

/**
 * @brief Calcula o valor do shift left lógico para inteiro. Retira dois operandos do topo da pilha
 * e faz o shift left do primeiro operando por s posições, onde s são os 5 bits menos significativos
 * do segundo operando. O resultado é colocado no topo da pilha
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void ishl(Frame* curr_frame) {
  if (DEBUG) cout << "----------ishl----------\n";
  curr_frame->pc++;

  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  int int_value_1 = operand_1->type_int;
  int int_value_2 = operand_2->type_int;
  if (DEBUG) cout << "int_value_1: " << int_value_1 << "\n";
  if (DEBUG) cout << "int_value_2: " << int_value_2 << "\n";

  int_value_1 &= 0x1f;
  if (DEBUG) cout << "int_value_1: " << int_value_1 << "\n";

  u4 int_result = int_value_2 << int_value_1;
  if (DEBUG) cout << "int_result: " << int_result << "\n";

  Operand* result = check_string_create_type("I");
  result->type_int = int_result;

  curr_frame->push_operand(result);
}

/**
 * @brief Calcula o valor do shift left lógico para long. Retira dois operandos do topo da pilha
 * e faz o shift left do primeiro operando por s posições, onde s são os 5 bits menos significativos
 * do segundo operando. O resultado é colocado no topo da pilha
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void lshl(Frame* curr_frame) {
  if (DEBUG) cout << "----------lshl----------\n";

  curr_frame->pc++;

  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  u8 l_value_1 = operand_1->type_long;
  u8 l_value_2 = operand_2->type_long;

  l_value_2 &= 0x0000003f;

  u8 l_result = l_value_1 << l_value_2;

  Operand* result = check_string_create_type("J");

  result->type_long = l_result;

  curr_frame->push_operand(result);
}

/**
 * @brief Calcula o valor do shift right lógico para inteiro. Retira dois operandos do topo da pilha
 * e faz o shift right do primeiro operando por s posições, onde s são os 5 bits menos significativos
 * do segundo operando. O resultado é colocado no topo da pilha
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void ishr(Frame* curr_frame) {
  if (DEBUG) cout << "----------ishr----------\n";
  curr_frame->pc++;

  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  int int_value_1 = operand_1->type_int;
  int int_value_2 = operand_2->type_int;

  if (DEBUG) cout << "int_value_1: " << int_value_1 << "\n";
  if (DEBUG) cout << "int_value_2: " << int_value_2 << "\n";

  u4 int_result = (u4) (int_value_2 / pow(2, int_value_1));
  if (DEBUG) cout << "int_result: " << int_result << "\n";

  Operand* result = check_string_create_type("I");
  result->type_int = int_result;

  curr_frame->push_operand(result);
}

/**
 * @brief Calcula o valor do shift right lógico para long. Retira dois operandos do topo da pilha
 * e faz o shift right do primeiro operando por s posições, onde s são os 5 bits menos significativos
 * do segundo operando. O resultado é colocado no topo da pilha
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void lshr(Frame* curr_frame) {
  if (DEBUG) cout << "----------lshr----------\n";

  curr_frame->pc++;

  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  u8 l_value_1 = operand_1->type_long;
  u8 l_value_2 = operand_2->type_long;
  u8 l_result = (u8) (l_value_1 / pow(2, l_value_2 & 0x3f));

  Operand* result = check_string_create_type("J");
  result->type_long = (u8) l_result;

  curr_frame->push_operand(result);
}

void iushr(Frame* curr_frame) {
  if (DEBUG) cout << "----------iushr----------\n";

  curr_frame->pc++;

  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  u4 i_value_1 = operand_1->type_int;
  u4 i_value_2 = operand_2->type_int;

  i_value_2 &= 0x0000001f;

  u4 i_result = i_value_1 >> i_value_2;
  Operand* result = check_string_create_type("I");

  result->type_int = i_result;

  curr_frame->push_operand(result);
}

void lushr(Frame* curr_frame) {
  if (DEBUG) cout << "----------lushr----------\n";

  curr_frame->pc++;

  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  u4 i_value_1 = operand_1->type_long;
  u4 i_value_2 = operand_2->type_long;

  i_value_2 &= 0x0000003f;

  u4 i_result = i_value_1 >> i_value_2;
  Operand* result = check_string_create_type("J");

  result->type_long = i_result;

  curr_frame->push_operand(result);
}

void iand(Frame* curr_frame) {
  if (DEBUG) cout << "----------iand----------\n";

    u4 ivalue1, ivalue2, iresult;
    curr_frame->pc++;

    Operand* value1 = curr_frame->pop_operand();
    Operand* value2 = curr_frame->pop_operand();

    ivalue1 = value1->type_int;
    ivalue2 = value2->type_int;
    iresult = ivalue1 & ivalue2;

    Operand* result = check_string_create_type("I");
    result->type_int = (u4)iresult;

    curr_frame->push_operand(result);
}

void land(Frame* curr_frame) {
  if (DEBUG) cout << "----------land----------\n";

  curr_frame->pc++;

  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  u8 i_value_1 = operand_1->type_long;
  u8 i_value_2 = operand_2->type_long;
  u8 i_result = i_value_1 & i_value_2;

  Operand* result = check_string_create_type("J");

  result->type_long = (u8) i_result;

  curr_frame->push_operand(result);
}

/**
 * @brief Realiza a operacao de OR entre dois operandos e empilha o resultado
 * @param curr_frame ponteiro para o frame atual
 * @return void
 */
void ior(Frame* curr_frame) {
  if (DEBUG) cout << "----------ior----------\n";

  u4 ivalue1, ivalue2, iresult;

  curr_frame->pc++;

  Operand* value1 = curr_frame->pop_operand();
  Operand* value2 = curr_frame->pop_operand();

  ivalue1 = value1->type_int;
  ivalue2 = value2->type_int;

  iresult = ivalue1 | ivalue2;

  Operand* result = check_string_create_type("I");

  result->type_int = (u4)iresult;

  curr_frame->push_operand(result);
}

void lor(Frame* curr_frame) {
  if (DEBUG) cout << "----------lor----------\n";

  curr_frame->pc++;
  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();
  u8 i_value_1 = operand_1->type_long;
  u8 i_value_2 = operand_2->type_long;
  u8 i_result = i_value_1 | i_value_2;

  Operand* result = check_string_create_type("J");
  result->type_long = (u8) i_result;
  curr_frame->push_operand(result);
}

void ixor(Frame* curr_frame) {
  if (DEBUG) cout << "----------ixor----------\n";

  curr_frame->pc++;

  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  u4 i_value_1 = operand_1->type_int;
  u4 i_value_2 = operand_2->type_int;
  u4 i_result = i_value_1 ^ i_value_2;

  Operand* result = check_string_create_type("I");

  result->type_int = (u4) i_result;

  curr_frame->push_operand(result);
}

void lxor(Frame* curr_frame) {
  if (DEBUG) cout << "----------lxor----------\n";
  curr_frame->pc++;

  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  u8 i_value_1 = operand_1->type_long;
  u8 i_value_2 = operand_2->type_long;
  u8 i_result = i_value_1 ^ i_value_2;

  Operand* result = check_string_create_type("I");
  result->type_long = (u8) i_result;

  curr_frame->push_operand(result);
}

/**
 * @brief Incrementa uma variavel local em uma constante
 * @param curr_frame Ponteiro para o frame atual
 * @return void
 */
void iinc(Frame* curr_frame) {
  if (DEBUG) cout << "----------iinc----------\n";
  curr_frame->pc++;

  u1 index = curr_frame->method_code->code[curr_frame->pc++];
  if (DEBUG) cout << "iinc index: " << (int) index  << "\n";

  u1 constant_value = curr_frame->method_code->code[curr_frame->pc++];
  if (DEBUG) cout << "iinc constant_value: " << (int) constant_value  << "\n";

  if (DEBUG) printf("local_variables_array.at(%d): %d \n", index, curr_frame->local_variables_array.at(index)->type_int);
  curr_frame->local_variables_array.at(index)->type_int += (int) constant_value;
}
