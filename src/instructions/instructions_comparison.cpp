/** @file instructions_comparison.cpp
 *  @brief Módulo que contém as instruções de opcode do tipo comparison da JVM.
 */

#include "interpreter.hpp"
#include <stdlib.h>

/*************************** COMPARISONS ***************************/
void lcmp(Frame* curr_frame) {
  if (DEBUG) cout << "----------lcmp----------\n";
  Operand* op2 = curr_frame->pop_operand();
  Operand* op1 = curr_frame->pop_operand();
  Operand* result = (Operand* ) malloc(sizeof(Operand));
  
  if(op1->type_long > op2->type_long)
    result->type_int = (int32_t)1;
  else if(op1->type_long == op2->type_long)
    result->type_int = (int32_t)0;
  else
    result->type_int = (int32_t)-1;

  result->tag = CONSTANT_INT;

  curr_frame->push_operand(result);
  curr_frame->pc++;
}

void fcmpl(Frame* curr_frame) {
  if (DEBUG) cout << "----------fcmpl----------\n";
  Operand* op2 = curr_frame->pop_operand();
  Operand* op1 = curr_frame->pop_operand();
  Operand* result = (Operand* ) malloc(sizeof(Operand));
  float op1f, op2f;
  memcpy(&op1f, &op1->type_float, sizeof(float));
  memcpy(&op2f, &op2->type_float, sizeof(float)); 

  if(op1f > op2f)
    result->type_int = (int32_t) 1;
  else if(op1f == op2f)
    result->type_int = (int32_t) 0;
  else if(op1f < op2f)
    result->type_int = (int32_t) -1;
  else
    result->type_int = (int32_t) -1;

  result->tag = CONSTANT_INT;

  curr_frame->push_operand(result);
  curr_frame->pc++; 
}

void fcmpg(Frame* curr_frame) {
  if (DEBUG) cout << "----------fcmpg----------\n";
  Operand* op2 = curr_frame->pop_operand();
  Operand* op1 = curr_frame->pop_operand();
  Operand* result = (Operand* ) malloc(sizeof(Operand));
  float op1f, op2f;
  memcpy(&op1f, &op1->type_float, sizeof(float));
  memcpy(&op2f, &op2->type_float, sizeof(float));

  if(op1f > op2f)
    result->type_int = (int32_t) 1;
  else if(op1f == op2f)
    result->type_int = (int32_t) 0;
  else if(op1f < op2f)
    result->type_int = (int32_t) -1;
  else
    result->type_int = (int32_t) 1;

  result->tag = CONSTANT_INT;

  curr_frame->push_operand(result);
  curr_frame->pc++;
}

void dcmpl(Frame* curr_frame) {
  if (DEBUG) cout << "----------dcmpl----------\n";
  Operand* op2 = curr_frame->pop_operand();
  Operand* op1 = curr_frame->pop_operand();
  Operand* result = (Operand* ) malloc(sizeof(Operand));
  double op1f, op2f;
  memcpy(&op1f, &op1->type_double, sizeof(double));
  memcpy(&op2f, &op2->type_double, sizeof(double)); 

  if(op1f > op2f)
    result->type_int = (int32_t) 1;
  else if(op1f == op2f)
    result->type_int = (int32_t) 0;
  else if(op1f < op2f)
    result->type_int = (int32_t) -1;
  else
    result->type_int = (int32_t) -1;

  result->tag = CONSTANT_INT;

  curr_frame->push_operand(result);
  curr_frame->pc++; 
}

void dcmpg(Frame* curr_frame) {
  if (DEBUG) cout << "----------dcmpg----------\n";
  Operand* op2 = curr_frame->pop_operand();
  Operand* op1 = curr_frame->pop_operand();
  Operand* result = (Operand* ) malloc(sizeof(Operand));
  double op1f, op2f;
  memcpy(&op1f, &op1->type_double, sizeof(double));
  memcpy(&op2f, &op2->type_double, sizeof(double));

  if(op1f > op2f)
    result->type_int = (int32_t) 1;
  else if(op1f == op2f)
    result->type_int = (int32_t) 0;
  else if(op1f < op2f)
    result->type_int = (int32_t) -1;
  else
    result->type_int = (int32_t) 1;

  result->tag = CONSTANT_INT;

  curr_frame->push_operand(result);
  curr_frame->pc++;
}

void ifeq(Frame* curr_frame) {
  Operand* op = curr_frame->pop_operand();
  int val = (int)op->type_int;
  if (val == 0) {
    int shift;
    shift = curr_frame->method_code->code[curr_frame->pc + 1];
    shift = (shift << 8 ) | curr_frame->method_code->code[curr_frame->pc + 2];
    curr_frame->pc += shift;
  } else {
    curr_frame->pc +=3;
  }
}

void ifne(Frame* curr_frame) {
  Operand* op = curr_frame->pop_operand();
  int val = (int)op->type_int;
  if (val != 0) {
    int shift;
    shift = curr_frame->method_code->code[curr_frame->pc + 1];
    shift = (shift << 8 ) | curr_frame->method_code->code[curr_frame->pc + 2];
    curr_frame->pc += shift;
  } else {
    curr_frame->pc +=3;
  }
}

void iflt(Frame* curr_frame) {
  Operand* op = curr_frame->pop_operand();
  int val = (int)op->type_int;
  if (val < 0) {
    int shift;
    shift = curr_frame->method_code->code[curr_frame->pc + 1];
    shift = (shift << 8 ) | curr_frame->method_code->code[curr_frame->pc + 2];
    curr_frame->pc += shift;
  } else {
    curr_frame->pc +=3;
  }
}

void ifge(Frame* curr_frame) {
  Operand* op = curr_frame->pop_operand();
  int val = (int)op->type_int;
  if (val >= 0) {
    int shift;
    shift = curr_frame->method_code->code[curr_frame->pc + 1];
    shift = (shift << 8 ) | curr_frame->method_code->code[curr_frame->pc + 2];
    curr_frame->pc += shift;
  } else {
    curr_frame->pc +=3;
  }
}

void ifgt(Frame* curr_frame) {
  Operand* op = curr_frame->pop_operand();
  int val = (int)op->type_int;
  if (val > 0) {
    int shift;
    shift = curr_frame->method_code->code[curr_frame->pc + 1];
    shift = (shift << 8 ) | curr_frame->method_code->code[curr_frame->pc + 2];
    curr_frame->pc += shift;
  } else {
    curr_frame->pc +=3;
  }
}

void ifle(Frame* curr_frame) {
  Operand* op = curr_frame->pop_operand();
  int val = (int)op->type_int;

  if (val <= 0) {
    int shift;
    shift = curr_frame->method_code->code[curr_frame->pc + 1];
    shift = (shift << 8 ) | curr_frame->method_code->code[curr_frame->pc + 2];
    curr_frame->pc += shift;
  } else {
    curr_frame->pc +=3;
  }
}

/**
 * @brief Compara valor1 = valor2. Se verdeiro, realiza salto
 * @param curr_frame ponteiro para o frame atual
 * @return void
 */
void if_icmpeq(Frame* curr_frame) {
  Operand* operand_1 = curr_frame->pop_operand();
  Operand* operand_2 = curr_frame->pop_operand();

  u4 value_operand_1 = operand_1->type_int;
  u4 value_operand_2 = operand_2->type_int;

  if(value_operand_2 == value_operand_1) {
    u2 offset;

    offset = curr_frame->method_code->code[curr_frame->pc + 1];
    offset = (offset << 8 ) | curr_frame->method_code->code[curr_frame->pc + 2];

    curr_frame->pc += offset;
  }else{
    curr_frame->pc +=3;
  }
}

/**
 * @brief Verifica se valor1 é diferente de valor2. Se for, realiza salto
 * @param curr_frame ponteiro para o frame atual
 * @return void
 */
void if_icmpne(Frame* curr_frame) {
  Operand* op1 = curr_frame->pop_operand();
  Operand* op2 = curr_frame->pop_operand();

  u4 value_op1 = op1->type_int;
  u4 value_op2 = op2->type_int;

  if(value_op2 != value_op1) {
    int16_t offset;

    offset = curr_frame->method_code->code[curr_frame->pc + 1];
    offset = (offset << 8 ) | curr_frame->method_code->code[curr_frame->pc + 2];

    curr_frame->pc += offset;
  }else{
    curr_frame->pc +=3;
  }
}

void if_icmplt(Frame* curr_frame) {
  Operand* op1 = curr_frame->pop_operand();
  Operand* op2 = curr_frame->pop_operand();

  int value = op1->type_int;
  int value2 = op2->type_int;

  if(value2 < value) {
    int shift;

    shift =curr_frame->method_code->code[curr_frame->pc + 1];
    shift = (shift << 8 ) | curr_frame->method_code->code[curr_frame->pc + 2];

    curr_frame->pc += shift;
  }else{
    curr_frame->pc +=3;
  }
}

/**
 * @brief Salta para outro endereço caso  parametro 1 for maior ou igual ao parametro 2
 * @param Frame* curr_frame ponteiro que aponta para o frame atual
 * @return void
 */
void if_icmpge(Frame* curr_frame) {
  if (DEBUG) cout << "----------if_icmpge----------\n";

  Operand* op1 = curr_frame->pop_operand();
  Operand* op2 = curr_frame->pop_operand();

  u4 param2_value = op1->type_int;
  u4 param1_value = op2->type_int;

  if (DEBUG) cout << "param1_value: " << param1_value  << "\n";
  if (DEBUG) cout << "param2_value: " << param2_value  << "\n";

  if (param1_value >= param2_value) {
    u2 jump;

    jump = curr_frame->method_code->code[curr_frame->pc + 1];
    jump = (jump << 8 ) | curr_frame->method_code->code[curr_frame->pc + 2];

    curr_frame->pc += jump;
  }else{
    curr_frame->pc += 3;
  }
}

void if_icmpgt(Frame* curr_frame) {
  Operand* op1 =curr_frame->pop_operand();
  Operand* op2 =curr_frame->pop_operand();

  int value = op1->type_int;
  int value2 = op2->type_int;

  if(value2 > value) {
      int shift;

      shift =curr_frame->method_code->code[curr_frame->pc + 1];
      shift = (shift << 8 ) | curr_frame->method_code->code[curr_frame->pc + 2];

     curr_frame->pc += shift;
  }else{
     curr_frame->pc +=3;
  }
}

void if_icmple(Frame* curr_frame) {
  Operand* op1 =curr_frame->pop_operand();
  Operand* op2 =curr_frame->pop_operand();

  int value = op1->type_int;
  int value2 = op2->type_int;

  if(value2 <= value) {
      int shift;

      shift =curr_frame->method_code->code[curr_frame->pc + 1];
      shift = (shift << 8 ) | curr_frame->method_code->code[curr_frame->pc + 2];

     curr_frame->pc += shift;
  }else{
     curr_frame->pc +=3;
  }
}

void if_acmpeq(Frame* curr_frame) {
  u2 branch = curr_frame->method_code->code[curr_frame->pc + 1];
  branch = (branch << 8) + curr_frame->method_code->code[curr_frame->pc + 2];

  Operand* op = curr_frame->pop_operand();
  Operand* op2 = curr_frame->pop_operand();

  if (op->class_container == op2->class_container) {
      curr_frame->pc += branch;
  }
  else{
      curr_frame->pc += 3;
  }
}

void if_acmpne(Frame* curr_frame) {
  u2 branch = curr_frame->method_code->code[curr_frame->pc + 1];
  branch = (branch << 8) + curr_frame->method_code->code[curr_frame->pc + 2];

  Operand* op = curr_frame->pop_operand();
  Operand* op2 = curr_frame->pop_operand();

  if (op->class_container != op2->class_container) {
      curr_frame->pc += branch;
  }
  else{
      curr_frame->pc += 3;
  }
}