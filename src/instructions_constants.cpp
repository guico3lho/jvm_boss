/** @file instructions_constants.cpp
 *  @brief Módulo que contém as instruções de opcode do tipo de constantes da JVM.
 *  @bug No know bugs.
 */
#include "interpreter.hpp"
#include "instructions_constants.hpp"

/*************************** CONSTANTS ***************************/
/** 
 * @brief Não faz nada, só incrementa pc.
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void nop(Frame *curr_frame) {
  curr_frame->pc++;
}

/** @brief Empurra o valor NULL na pilha de operandos
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void aconst_null(Frame* curr_frame) {
    Operand *op = (Operand*)malloc(sizeof(Operand));
    op->tag = CONSTANT_EMPTY;
    curr_frame->push_operand(op);
    curr_frame->pc++;
}

/** @brief Empurra int na pilha de operandos
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void iconst_m1(Frame* curr_frame) {
    Operand *op = (Operand*)malloc(sizeof(Operand));
    op->tag = CONSTANT_INT;
    op->type_int = -1;
    curr_frame->push_operand(op);
    curr_frame->pc++;
}

/** @brief Empurra int na pilha de operandos
 * @param *curr_frame ponteiro para o frame atualiconst_2
 * @return void
 */
void iconst_0(Frame* curr_frame) {
  Operand *op = (Operand*)malloc(sizeof(Operand));
  op->tag = CONSTANT_INT;
  op->type_int = 0;
  curr_frame->push_operand(op);
  curr_frame->pc++;

  if (DEBUG) cout << "iconst_0\n";
}

/** @brief ...
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void iconst_1(Frame* curr_frame) {
  if (DEBUG) cout << "\n----------iconst_1----------\n";

    Operand *op = (Operand*)malloc(sizeof(Operand));
    op->tag = CONSTANT_INT;
    op->type_int = 1;
    curr_frame->push_operand(op);

    curr_frame->pc++;
}

/** @brief Empurra int na pilha de operandos
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void iconst_2(Frame* curr_frame) {
    Operand *op = (Operand*)malloc(sizeof(Operand));
    op->tag = CONSTANT_INT;
    op->type_int = 2;
    curr_frame->push_operand(op);
    curr_frame->pc++;

    if (DEBUG) cout << "iconst_2\n";
}

/** @brief Empurra int na pilha de operandos
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void iconst_3(Frame* curr_frame) {
    Operand *op = (Operand*)malloc(sizeof(Operand));
    op->tag = CONSTANT_INT;
    op->type_int = 3;
    curr_frame->push_operand(op);
    curr_frame->pc++;

    if (DEBUG) cout << "iconst_3\n";
}

/** @brief Empurra int na pilha de operandos
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void iconst_4(Frame* curr_frame) {
  Operand *op = (Operand*)malloc(sizeof(Operand));
  op->tag = CONSTANT_INT;
  op->type_int = 4;
  curr_frame->push_operand(op);
  curr_frame->pc++;

  if (DEBUG) cout << "iconst_4\n";
}

/** @brief Empurra int na pilha de operandos
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void iconst_5(Frame* curr_frame) {
  Operand *op = (Operand*)malloc(sizeof(Operand));
  op->tag = CONSTANT_INT;
  op->type_int = 5;
  curr_frame->push_operand(op);
  curr_frame->pc++;

  if (DEBUG) cout << "iconst_5\n";
}

/**
 * @brief Empilha a constante long 0 na pilha de opreandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void lconst_0(Frame *curr_frame) {
    Operand *op = (Operand*)malloc(sizeof(Operand));
    op->tag = CONSTANT_LONG;
    op->type_long = 0;
    curr_frame->operand_stack.push(op);
    curr_frame->pc++;
}

/**
 * @brief Empilha a constante long 1 na pilha de operandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void lconst_1(Frame *curr_frame) {
  Operand *op = (Operand*)malloc(sizeof(Operand));
  op->tag = CONSTANT_LONG;
  op->type_long = 1;
  curr_frame->push_operand(op);
  curr_frame->pc++;

  if (DEBUG) cout << "lconst_1\n";
}

/**
 * @brief Empilha a constante float 0 na pilha de operandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void fconst_0(Frame *curr_frame) {
    Operand *op = (Operand*)malloc(sizeof(Operand));
    op->tag = CONSTANT_FLOAT;
    op->type_long = 0.0;
    curr_frame->operand_stack.push(op);
    curr_frame->pc++;
}

/**
 * @brief Empilha a constante float 1 na pilha de operandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void fconst_1(Frame *curr_frame) {
    Operand *op = (Operand*)malloc(sizeof(Operand));
    op->tag = CONSTANT_FLOAT;
    op->type_long = 1.0;
    curr_frame->operand_stack.push(op);
    curr_frame->pc++;

    if (DEBUG) cout << "fconst_1\n";
}

/**
 * @brief Empilha a constante float 0 na pilha de operandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void fconst_2(Frame *curr_frame) {
    Operand *op = (Operand*)malloc(sizeof(Operand));
    op->tag = CONSTANT_FLOAT;
    op->type_long = 2.0;
    curr_frame->operand_stack.push(op);
    curr_frame->pc++;
}

/**
 * @brief Empilha a constante double 0 na pilha de operandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void dconst_0(Frame *curr_frame) {
    Operand *op = (Operand*)malloc(sizeof(Operand));
    op->tag = CONSTANT_DOUBLE;

    op->type_double = 0.0;
    curr_frame->operand_stack.push(op);
    curr_frame->pc++;
}

/**
 * @brief Empilha a constante double 1 na pilha de operandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void dconst_1(Frame *curr_frame) {
  Operand *op = (Operand*)malloc(sizeof(Operand));
  op->tag = CONSTANT_DOUBLE;

  op->type_double = 1.0;
  curr_frame->operand_stack.push(op);
  curr_frame->pc++;

  if (DEBUG) cout << "dconst_1\n";
}

/**
 * @brief Empilha int composto por byte de argumento na pilha de operandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void bipush(Frame *curr_frame) {
  if (DEBUG) cout << "\n----------bipush----------\n";

  curr_frame->pc++;

  Operand *op = (Operand*)malloc(sizeof(Operand));
  u1 byte = curr_frame->method_code->code[curr_frame->pc++];
  if (DEBUG) cout << "bipush byte " << byte << "\n";

  op->tag = CONSTANT_INT;
  op->type_int = (int8_t) byte;
  curr_frame->operand_stack.push(op);

}

/**
 * @brief Empilha int composto por byte de argumento na pilha de operandos
 * @param *curr_frame Ponteiro para o frame atual
 * @return void
 */
void sipush(Frame *curr_frame) {
    Operand *op = (Operand*)malloc(sizeof(Operand));
    u1 byte = curr_frame->method_code->code[curr_frame->pc++];
    u1 byte2 = curr_frame->method_code->code[curr_frame->pc++];
    op->tag = CONSTANT_INT;
    op->type_int = (byte<<8)|byte2;
    curr_frame->operand_stack.push(op);

}

/** @brief Coloca na pilha de operandos uma constante do tamanho de uma word.
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void ldc(Frame *curr_frame) {
  if (DEBUG) cout << "\n----------ldc----------\n";

  curr_frame->pc++;
  Operand *op = (Operand*) malloc(sizeof(Operand));

  u1 index = curr_frame->method_code->code[curr_frame->pc++];
  if (DEBUG) cout << "ldc index: " << (int) index << "\n";

  Cp_Info &cp_info = curr_frame->cp_reference[((int)index)];
  op->tag = cp_info.tag;
  if (DEBUG) cout << "op->tag: " << (int) op->tag << "\n";

  switch (op->tag) {
    case CONSTANT_INT:
      op->type_int = cp_info.Integer.bytes;
      break;
    case CONSTANT_FLOAT:
      op->type_float = (float) cp_info.Float.bytes;
      if (DEBUG) cout << "ldc value: " << (float) op->type_float << "\n";
      break;
    case CONSTANT_STRING: {
      if (DEBUG) printf("Magic Number: 0x%0X\n", curr_frame->class_file_ref->magic_number);
      // string string_utf8 = get_cp_info_utf8(*(curr_frame->class_file_ref), cp_info.String.string_index);

      string string_utf8 = get_utf8_constant_pool(curr_frame->cp_reference, cp_info.String.string_index);
      if (DEBUG) cout << "string_utf8: " << string_utf8 << "\n";

      op->type_string = new string(string_utf8); 
    }
      break;
    case CONSTANT_CLASS: // TODO
      break;
    default:
      // CONSTANT_METHOD_HANDLE
      // CONSTANT_METHOD_REF
      break;
  }

    curr_frame->push_operand(op);
}

/** @brief Dá push de uma word na pilha de operandos.
@param Frame *curr_frame ponteiro que aponta para o frame atual
@return void
*/
void ldc_w(Frame *curr_frame) {
    curr_frame->pc++;

    u1 index_1 = curr_frame->method_code->code[curr_frame->pc++];
    u1 index_2 = curr_frame->method_code->code[curr_frame->pc++];

    u2 index = (index_1 << 8) + index_2;

    Cp_Info *cp_info = curr_frame->cp_reference + (int)index;
    Operand* operands = nullptr;

    switch(cp_info->tag) {
        case CONSTANT_INT:
            operands = (Operand*)malloc(sizeof(Operand));
            operands->tag = CONSTANT_INT;
            operands->type_int = cp_info->Integer.bytes;
            break;
        case CONSTANT_FLOAT:
            operands = (Operand*)malloc(sizeof(Operand));
            operands->tag = CONSTANT_FLOAT;
            operands->type_float = cp_info->Float.bytes;
            break;
        case CONSTANT_CLASS:
            //TODO
            printf("TODO");
            break;
        case CONSTANT_STRING:{
            operands = (Operand*)malloc(sizeof(Operand));
            operands->tag = CONSTANT_STRING;
            string utf8_cp = get_utf8_constant_pool(curr_frame->cp_reference, cp_info->String.string_index);

            operands->type_string = new string(utf8_cp);
            break;
        }
        default:
            //TODO
            printf("TODO");
            break; //methodRef e methodHandle não implementados
    }

    curr_frame->push_operand(operands);

}

/** @brief Dá push em duas words na pilha de operandos.
 * @param *curr_frame ponteiro que aponta para o frame atual
 * @return void
 */
void ldc2_w(Frame *curr_frame) {
  if (DEBUG) cout << "\n----------ldc2_w----------\n";
  curr_frame->pc++;

  u1 index_1 = curr_frame->method_code->code[curr_frame->pc++];
  u1 index_2 = curr_frame->method_code->code[curr_frame->pc++];

  u2 index = (index_1 << 8) + index_2;

  if (DEBUG) cout << "ldc2_w index : " << (int)index << "\n";
  Cp_Info *cp_info = curr_frame->cp_reference + (int)index;
  Operand* operands;

  if (cp_info->tag == CONSTANT_DOUBLE) { // double
    operands = (Operand*)malloc(sizeof(Operand));
    operands->tag = CONSTANT_DOUBLE;
    operands->type_double = cp_info->Double.high_bytes;
    operands->type_double = (operands->type_double << 32) + cp_info->Double.low_bytes;

    if (DEBUG) {
      double double_v;
      memcpy(&double_v, &operands->type_double, sizeof(double));
      printf("double value: %.15lf\n", double_v);
    }
  } else { // long
    operands = (Operand*) malloc(sizeof(Operand));
    operands->tag = CONSTANT_LONG;

    long read_long_value;
    memcpy(&read_long_value, &(cp_info->Long.high_bytes),sizeof(long));
    memcpy(&read_long_value, &(cp_info->Long.low_bytes),sizeof(long));

    operands->type_long = read_long_value;
    if (DEBUG) cout << "long value: " << operands->type_double << "\n";
  }
  curr_frame->push_operand(operands);
}

