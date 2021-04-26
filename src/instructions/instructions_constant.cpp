/** @file instructions_constants.cpp
 *  @brief Módulo que contém as instruções de opcode do tipo constante da JVM.
 */

#include "interpreter.hpp"

/*************************** CONSTANTS ***************************/
/** 
 *  @brief Não faz nada, só incrementa pc.
 *  @param *curr_frame ponteiro para o frame atual
 *  @return void
 */
void nop(Frame *curr_frame) {
  if (DEBUG) cout << "----------nop----------\n";

  curr_frame->pc++;
}

/** @brief Empurra o valor NULL na pilha de operandos
 *  @param *curr_frame ponteiro para o frame atual
 *  @return void
 */
void aconst_null(Frame* curr_frame) {
  if (DEBUG) cout << "----------aconst_null----------\n";

  Operand *op = (Operand*) malloc(sizeof(Operand));

  op->tag = CONSTANT_EMPTY;

  curr_frame->push_operand(op);
  curr_frame->pc++;
}

/** @brief Adiciona int na pilha de operandos de acordo com o valor enviado nos parâmetros
 *  @param *curr_frame ponteiro para o frame atual
 *  @param value
 *  @return void
 */
void iconst_n(Frame* curr_frame, int n) {
  if (DEBUG) cout << "----------iconst_" << n << "----------\n";

  Operand *op = (Operand*) malloc(sizeof(Operand));

  op->tag = CONSTANT_INT;
  op->type_int = n;

  curr_frame->push_operand(op);
  curr_frame->pc++;
}

/** @brief Adiciona -1 na pilha de operandos
 *  @param *curr_frame ponteiro para o frame atual
 *  @return void
 */
void iconst_m1(Frame* curr_frame) {
  iconst_n(curr_frame, -1);
}

/** @brief Adiciona 0 na pilha de operandos
 *  @param *curr_frame ponteiro para o frame atualiconst_2
 *  @return void
 */
void iconst_0(Frame* curr_frame) {
    iconst_n(curr_frame, 0);
}

/** @brief Adiciona 1 na pilha de operandos
 *  @param *curr_frame ponteiro para o frame atual
 *  @return void
 */
void iconst_1(Frame* curr_frame) {
    iconst_n(curr_frame, 1);
}

/** @brief Adiciona 2 na pilha de operandos
 *  @param *curr_frame ponteiro para o frame atual
 *  @return void
 */
void iconst_2(Frame* curr_frame) {
    iconst_n(curr_frame, 2);
}

/** @brief Adiciona 3 na pilha de operandos
 *  @param *curr_frame ponteiro para o frame atual
 *  @return void
 */
void iconst_3(Frame* curr_frame) {
    iconst_n(curr_frame, 3);
}

/** @brief Adiciona 4 na pilha de operandos
 *  @param *curr_frame ponteiro para o frame atual
 *  @return void
 */
void iconst_4(Frame* curr_frame) {
    iconst_n(curr_frame, 4);
}

/** @brief Adiciona 5 na pilha de operandos
 *  @param *curr_frame ponteiro para o frame atual
 *  @return void
 */
void iconst_5(Frame* curr_frame) {
    iconst_n(curr_frame, 5);
}

/**
 *  @brief Adiciona a constante long 0 na pilha de operandos
 *  @param *curr_frame Ponteiro para o frame atual
 *  @return void
 */
void lconst_n(Frame *curr_frame, long n) {
  if (DEBUG) cout << "----------lconst_" << n << "----------\n";

  Operand *op = (Operand*) malloc(sizeof(Operand));

  op->tag = CONSTANT_LONG;
  op->type_long = n;

  curr_frame->operand_stack.push(op);
  curr_frame->pc++;
}

/**
 *  @brief Adiciona a constante long 0 na pilha de opreandos
 *  @param *curr_frame Ponteiro para o frame atual
 *  @return void
 */
void lconst_0(Frame *curr_frame) {
  lconst_n(curr_frame, 0);
}

/**
 *  @brief Adiciona a constante long 1 na pilha de operandos
 *  @param *curr_frame Ponteiro para o frame atual
 *  @return void
 */
void lconst_1(Frame *curr_frame) {
  lconst_n(curr_frame, 1);
}

/**
 *  @brief Adiciona a constante float 0 na pilha de operandos
 *  @param *curr_frame Ponteiro para o frame atual
 *  @return void
 */
void fconst_n(Frame *curr_frame, float n) {
  if (DEBUG) cout << "----------fconst_" << n << "----------\n";

  Operand *op = (Operand*) malloc(sizeof(Operand));

  op->tag = CONSTANT_FLOAT;
  u4 float_bits = float_value_to_bits(n);
  op->type_float = float_bits;

  curr_frame->operand_stack.push(op);
  curr_frame->pc++;
}

/**
 *  @brief Adiciona a constante float 0 na pilha de operandos
 *  @param *curr_frame Ponteiro para o frame atual
 *  @return void
 */
void fconst_0(Frame *curr_frame) {
  fconst_n(curr_frame, 0.0);
}

/**
 *  @brief Adiciona a constante float 1 na pilha de operandos
 *  @param *curr_frame Ponteiro para o frame atual
 *  @return void
 */
void fconst_1(Frame *curr_frame) {
  fconst_n(curr_frame, 1.0);
}

/**
 *  @brief Adiciona a constante float 0 na pilha de operandos
 *  @param *curr_frame Ponteiro para o frame atual
 *  @return void
 */
void fconst_2(Frame *curr_frame) {
  fconst_n(curr_frame, 2.0);
}

/**
 *  @brief Adiciona a constante double na pilha de operandos
 *  @param *curr_frame Ponteiro para o frame atual
 *  @return void
 */
void dconst_n(Frame *curr_frame, double n) {
  if (DEBUG) cout << "----------dconst_" << n << "----------\n";

  Operand *op = (Operand*) malloc(sizeof(Operand));

  op->tag = CONSTANT_DOUBLE;
  u8 double_bits = double_value_to_bits(n);
  op->type_double = double_bits;

  curr_frame->operand_stack.push(op);
  curr_frame->pc++;
}

/**
 *  @brief Adiciona a constante double 0 na pilha de operandos
 *  @param *curr_frame Ponteiro para o frame atual
 *  @return void
 */
void dconst_0(Frame *curr_frame) {
  dconst_n(curr_frame, 0.0);
}

/**
 *  @brief Adiciona a constante double 1 na pilha de operandos
 *  @param *curr_frame Ponteiro para o frame atual
 *  @return void
 */
void dconst_1(Frame *curr_frame) {
  dconst_n(curr_frame, 1.0);
}

/**
 *  @brief Adiciona int composto por byte de argumento na pilha de operandos
 *  @param *curr_frame Ponteiro para o frame atual
 *  @return void
 */
void bipush(Frame *curr_frame) {
  if (DEBUG) cout << "----------bipush----------\n";

  Operand *op = (Operand*) malloc(sizeof(Operand));
  
  curr_frame->pc++;
  u1 byte = curr_frame->method_code->code[curr_frame->pc++];

  if (DEBUG) printf("bipush byte: %d (0x%0X)\n", (int) byte, byte);

  op->tag = CONSTANT_INT;
  op->type_int = (int8_t) byte;

  curr_frame->operand_stack.push(op);
}

/**
 *  @brief Adiciona int composto por byte de argumento na pilha de operandos
 *  @param *curr_frame Ponteiro para o frame atual
 *  @return void
 */
void sipush(Frame *curr_frame) {
  if (DEBUG) cout << "----------sipush----------\n";
  if (DEBUG) printf("Current PC: %d\n", (int) curr_frame->pc);

  Operand *op = (Operand*) malloc(sizeof(Operand));

  curr_frame->pc++;
  u1 byte = curr_frame->method_code->code[curr_frame->pc++];
  u1 byte2 = curr_frame->method_code->code[curr_frame->pc++];

  op->tag = CONSTANT_INT;
  op->type_int = (byte << 8) | byte2;

  curr_frame->operand_stack.push(op);
}

/** @brief Coloca na pilha de operandos uma constante do tamanho de uma word
 *  @param *curr_frame ponteiro para o frame atual
 *  @return void
 */
void ldc(Frame *curr_frame) {
  if (DEBUG) cout << "----------ldc----------\n";

  Operand *op = (Operand*) malloc(sizeof(Operand));

  curr_frame->pc++;

  int index = curr_frame->method_code->code[curr_frame->pc++];
  if (DEBUG) cout << "ldc index: " << index << "\n";

  Cp_Info cp_info = curr_frame->cp_reference[index];
  op->tag = cp_info.tag;
  u1 tag = op->tag;

  if (DEBUG) cout << "operand->tag: " << (int) op->tag << "\n";

  switch (tag) {
    case CONSTANT_INT:
      op->type_int = (int) cp_info.Integer.bytes;
      break;

    case CONSTANT_FLOAT:
      op->type_float = (float) cp_info.Float.bytes;
      if (DEBUG) cout << "ldc value: " << (float) op->type_float << "\n";
      break;

    case CONSTANT_STRING: {
      if (DEBUG) printf("Magic Number: 0x%0X\n", curr_frame->class_file_ref->magic_number);

      string string_utf8 = get_utf8_constant_pool(curr_frame->cp_reference, cp_info.String.string_index);
      if (DEBUG) cout << "string_utf8: " << string_utf8 << "\n";

      op->type_string = new string(string_utf8); 
    }
      break;

    case CONSTANT_CLASS: 
    if (DEBUG) printf("TODO");
      break;

    default:
      break;
  }

  curr_frame->push_operand(op);
}

/** @brief Dá push de uma word na pilha de operandos.
@param Frame *curr_frame ponteiro que aponta para o frame atual
@return void
*/
void ldc_w(Frame *curr_frame) {
  if (DEBUG) cout << "----------ldc_w----------\n";

  Operand* op = (Operand*) malloc(sizeof(Operand));

  curr_frame->pc++;

  int index = get_method_code_index(curr_frame);
  Cp_Info *cp_info = curr_frame->cp_reference + index;
  u2 tag = cp_info->tag;
  string utf8_cp;
  
  switch(tag) {
    case CONSTANT_INT:
      op->tag = CONSTANT_INT;
      op->type_int = (int) cp_info->Integer.bytes;
      break;

    case CONSTANT_FLOAT:
      op->tag = CONSTANT_FLOAT;
      op->type_float = (float) cp_info->Float.bytes;
      break;

    case CONSTANT_CLASS:
      if (DEBUG) printf("TODO");
      break;

    case CONSTANT_STRING:
      op->tag = CONSTANT_STRING;
      utf8_cp = get_utf8_constant_pool(curr_frame->cp_reference, cp_info->String.string_index);
      op->type_string = new string(utf8_cp);
      break;
    
    default:
      if (DEBUG) printf("TODO");
      break;
  }
  curr_frame->push_operand(op);
}

/** @brief Dá push em duas words na pilha de operandos
 *  @param *curr_frame ponteiro que aponta para o frame atual
 *  @return void
 */
void ldc2_w(Frame *curr_frame) {
  if (DEBUG) cout << "----------ldc2_w----------\n";

  Operand *op = (Operand*) malloc(sizeof(Operand));

  curr_frame->pc++;

  int index = get_method_code_index(curr_frame);
  if (DEBUG) cout << "ldc2_w index : " << index << "\n";

  Cp_Info *cp_info = (curr_frame->cp_reference) + index;
  u2 tag = cp_info->tag;
  op->tag = tag; //

  if (tag == CONSTANT_DOUBLE) { 
    // op->tag = CONSTANT_DOUBLE;
    op->type_double = cp_info->Double.high_bytes;
    op->type_double = (op->type_double << 32) + cp_info->Double.low_bytes;

    if (DEBUG) {
      double double_v;
      memcpy(&double_v, &op->type_double, sizeof(double));
      printf("double value: %.15lf\n", double_v);
    }

  } else {
    // ops->tag = CONSTANT_LONG;
    long read_long_value;

    memcpy(&read_long_value, &(cp_info->Long.high_bytes), sizeof(long));
    memcpy(&read_long_value, &(cp_info->Long.low_bytes), sizeof(long));

    op->type_long = read_long_value;

    if (DEBUG) cout << "long value: " << op->type_double << "\n";
  }
  curr_frame->push_operand(op);
}
