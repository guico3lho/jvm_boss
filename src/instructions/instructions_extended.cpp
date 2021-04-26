/** @file instructions_extended.cpp
 *  @brief Módulo que contém as instruções tipo extendidas da JVM.
*/

#include "interpreter.hpp"

/*************************** EXTENDED ***************************/

/**
 * @brief Define o tipo de dado dos operandos do newarray 
 * 
 * @param Operand *operand
 * @param u4 count
 * @param string array_type 
 */
std::vector<Operand*>* set_newarray(Operand* operand, u4 count, string array_type) {
  for (int i = 0; i < (int) count; i++) {
    operand->array_type->array->emplace_back(check_string_create_type(array_type));
  }

  return operand->array_type->array;
}

/**
 * @brief Função para instrução multianewarray de array multidimensionais
 * 
 * @param curr_frame 
 */
void multianewarray(Frame* curr_frame) {
  if (DEBUG) cout << "----------multianewarray----------\n";
  curr_frame->pc++;

  u2 index = get_method_code_index(curr_frame);
  if (DEBUG) cout << "CP index: " << (int) index << "\n";

  Cp_Info class_info = curr_frame->cp_reference[index]; // class, array, or interface type
  string class_name = get_utf8_constant_pool(curr_frame->cp_reference, class_info.Class.class_name);
  if (DEBUG) cout << "Nome da classe: " << class_name << "\n";

  string data_type;
  data_type.push_back(class_name.back());
  if (DEBUG) cout << "Tipo de dado: " << data_type << "\n";

  u1 dimensions = curr_frame->method_code->code[curr_frame->pc++];
  if (DEBUG) cout << "Dimensions: " << (int) dimensions << "\n";

  Operand *op_aux;

  //* Cria vetor de tamanhos dos arrays
  std::vector<int> counts = std::vector<int>(dimensions);

  for (int i = 0; i < dimensions; i++){
    op_aux = curr_frame->pop_operand();
    int count = op_aux->type_int;
    if (DEBUG) printf("array count %d: %d\n", i, count);
    counts[i] = count;
  }

  Operand *multiarray_ref = check_string_create_type("[");
  if (DEBUG) cout << "--------------------\n";

  //* ptr de vetor de ptrs de operandos..
  std::vector<Operand*>* array_ref = multiarray_ref->array_type->array;

  //* Começa pela dimensao mais externa: array raiz
  for (int i = 0; i < counts[0]; i++) {
    if (DEBUG) printf("Array [%d] - ", i);
    array_ref->emplace_back(check_string_create_type("["));
  }

  if (DEBUG) printf("\narray_ref address: %X | size: %d\n", array_ref, array_ref->size());
  if (DEBUG) cout << "--------------------\n";

  std::vector<Operand*>* array_ref_2;
  std::vector<Operand*>* array_ref_3;

  string string_array_type = "]";
  string string_int_type = "I";


  for (int i = 0; i < counts[0]; i++) {
    array_ref_2 = array_ref[0][i]->array_type->array;

    for (int j = 0; j < counts[1]; j++) {
      if (DEBUG) printf("Array [%d][%d] - ", i, j);
      array_ref_2->emplace_back(check_string_create_type("["));

      op_aux = array_ref_2[0][j];
      if (DEBUG) printf("op_aux[0][%d] address: %X\n\n", j, op_aux);
    }

    if (DEBUG) printf("\narray_ref_2 address: %X | size: %d\n", array_ref_2, array_ref_2->size());
    if (DEBUG) cout << "--------------------\n";
  }


  for (int i = 0; i < counts[0]; i++) {
    array_ref_2 = array_ref[0][i]->array_type->array; 
    if (DEBUG) printf("array_ref_2 address: %X | size: %d\n\n", array_ref_2, array_ref_2->size());

    for (int j = 0; j < counts[1]; j++) {

      op_aux = array_ref_2[0][j]; //! ERROR
      if (DEBUG) printf("op_aux[0][%d] address: %X\n", j, op_aux);

      array_ref_3 = op_aux->array_type->array;

      for (int k = 0; k < counts[2]; k++) {
        if (DEBUG) printf("Array [%d][%d][%d] - ", i, j, k);
        array_ref_3->emplace_back(check_string_create_type("I"));
      }

      if (DEBUG) printf("\narray_ref_3 address: %X | size: %d\n", array_ref_3, array_ref_3->size());
      if (DEBUG) cout << "--------------------\n";

    }
  }
  

  curr_frame->push_operand(multiarray_ref); 
  // curr_frame->pc++;
}

/**
 * @brief 
 * 
 * @param *curr_frame 
 */
void ifnull(Frame *curr_frame) {
  if (DEBUG) cout << "----------ifnull----------\n";
  Operand *operand = curr_frame->pop_operand();

  if (!(operand->type_int)) {
    int shift;
    shift = curr_frame->method_code->code[curr_frame->pc + 1];
    shift = (shift << 8 ) | curr_frame->method_code->code[curr_frame->pc + 2];
    curr_frame->pc += shift;
  } else {
    curr_frame->pc += 3;
  }
}

/**
 * @brief 
 * 
 * @param *curr_frame 
 */
void ifnonnull(Frame *curr_frame) {
  if (DEBUG) cout << "----------ifnonnull----------\n";

  Operand *operand = curr_frame->pop_operand();

  if (operand->type_int) {
    int shift;
    shift = curr_frame->method_code->code[curr_frame->pc + 1];
    shift = (shift << 8 ) | curr_frame->method_code->code[curr_frame->pc + 2];
    curr_frame->pc += shift;
  } else {
    curr_frame->pc += 3;
  }
}