/** @file instructions_extended.cpp
 *  @brief Módulo que contém as instruções tipo extendidas da JVM.
*/

#include "interpreter.hpp"

/*************************** EXTENDED ***************************/

/**
 * @brief Define o tipo de dado dos operandos do newarray 
 * @param operand
 * @param count
 * @param array_type 
 * @return std::vector<Operand*>*
 */
Operand* set_multianewarray(Operand* operand, int count, string array_type) {
  std::vector<Operand*>* array_ref = operand->array_type->array;

  for (int i = 0; i < count; i++) {
    array_ref->emplace_back(check_string_create_type(array_type));
  }

  if (DEBUG) printf("\narray_ref address: %p | size: %d\n", &array_ref, array_ref->size());
  if (DEBUG) cout << "--------------------\n";

  return operand;
}

/**
 * @brief Função para instrução multianewarray de array multidimensionais
 * @param curr_frame ponteiro para o frame atual 
 * @return void
 */
void multianewarray(Frame* curr_frame) {
  if (DEBUG) cout << "----------multianewarray----------\n";
  curr_frame->pc++;

  int i, j, k, l;
  u2 index = get_method_code_index(curr_frame);
  if (DEBUG) cout << "CP index: " << (int) index << "\n";

  Cp_Info class_info = curr_frame->cp_reference[index]; 
  string class_name = get_utf8_constant_pool(curr_frame->cp_reference, class_info.Class.class_name);
  if (DEBUG) cout << "Nome da classe: " << class_name << "\n";

  u1 dimensions = curr_frame->method_code->code[curr_frame->pc++];
  if (DEBUG) cout << "Dimensions: " << (int) dimensions << "\n";

  string data_type;
  data_type = class_name.substr(dimensions, class_name.length() - dimensions);
  if (DEBUG) cout << "Tipo de dado: " << data_type << "\n";

  Operand* op_aux;
  string string_array_type = "[";

  std::vector<int> counts = std::vector<int>(dimensions);

  for (i = 0; i < dimensions; i++) {
    op_aux = curr_frame->pop_operand();
    int count = op_aux->type_int;
    if (DEBUG) printf("array count %d: %d\n", i, count);
    counts[i] = count;
  }

  Operand* multiarray_ref = check_string_create_type("[");
  if (DEBUG) cout << "--------------------\n";

  std::vector<Operand*>* array_ref = multiarray_ref->array_type->array;
  std::vector<Operand*>* array_ref_2;

  for (i = 0; i < dimensions; i++) {

    if (i == (dimensions - 1)) string_array_type = data_type;
    if (DEBUG) cout << "Tipo de dado: " << string_array_type << "\n";

    if(i == 0) {
      for (j = 0; j < counts[i]; j++) {
        if (DEBUG) printf("Array [%d] - ", j);
        array_ref->emplace_back(check_string_create_type(string_array_type));
      }

      if (DEBUG) printf("\narray_ref address: %p | size: %d\n", &array_ref, array_ref->size());
      if (DEBUG) cout << "--------------------\n";
    }

    if(i == 1) {
      for (j = 0; j < counts[i - 1]; j++) {
        array_ref_2 = array_ref[0][j]->array_type->array;

        for (k = 0; k < counts[i]; k++) {
          if (DEBUG) printf("Array [%d][%d] - ", j, k);
          array_ref_2->emplace_back(check_string_create_type(string_array_type));
        }
      }
    }

    if(i == 2) {
      std::vector<Operand*>* array_ref_3;

      for (j = 0; j < counts[i - 2]; j++) {
        array_ref_2 = array_ref[0][j]->array_type->array; 

        for (k = 0; k < counts[i - 1]; k++) {
          array_ref_3 = array_ref_2[0][k]->array_type->array;

          for (l = 0; l < counts[i]; l++) {
            if (DEBUG) printf("Array [%d][%d][%d] - ", j, k, l);
            array_ref_3->emplace_back(check_string_create_type(string_array_type));
          }

          if (DEBUG) printf("\narray_ref_3 address: %p | size: %d\n", array_ref_3, array_ref_3->size());
          if (DEBUG) cout << "--------------------\n";
        }
      }
    }
  }
  
  curr_frame->push_operand(multiarray_ref); 
}

/**
 * @brief Condição igual a nulo
 * @param curr_frame ponteiro para o frame atual 
 * @return void
 */
void ifnull(Frame* curr_frame) {
  if (DEBUG) cout << "----------ifnull----------\n";
  Operand* operand = curr_frame->pop_operand();

  if (!(operand->type_int)) {
    u2 index = get_method_code_index(curr_frame);
    curr_frame->pc += index + 1;
  } else {
    curr_frame->pc += 3;
  }
}

/**
 * @brief Condição diferente de nulo
 * @param curr_frame ponteiro para o frame atual 
 * @return void
 */
void ifnonnull(Frame* curr_frame) {
  if (DEBUG) cout << "----------ifnonnull----------\n";

  Operand* op = curr_frame->pop_operand();

  if (op->type_int) {
    u2 index = get_method_code_index(curr_frame);
    curr_frame->pc += index + 1;

    if (DEBUG) cout << "CP index: " << (int) index << "\n";
  } else {
    curr_frame->pc += 3;
  }
}