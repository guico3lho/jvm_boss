/** @file instructions_extended.cpp
 *  @brief Módulo que contém as instruções tipo extendidas da JVM.
*/

#include "interpreter.hpp"

/*************************** EXTENDED ***************************/

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

  //* Cria vetor de tamanhos dos arrays
  // std::vector<int> counts = std::vector<int>(dimensions);
  // for (int i = dimensions; i < 0; i--){
  //   counts[i] = count;
  // }

  // for (int i = 0; i < dimensions; i++){
  //   if (DEBUG) printf("counts[%d]: %d\n", i, (int) counts[i]);
  // }
  
  // std::vector<Operand*> operands = std::vector<Operand*>(count);
  // std::vector<Operand*> op_vector;
    // operands[i] = (Operand*) malloc( ((int) count) * sizeof(Operand));

  Operand *array_ref = check_string_create_type("[");
  Operand *operand;
  Operand *op_aux;

  //* Começa pela ultima dimensao mais externa
  for (int i = 0; i < dimensions; i++){

    op_aux = curr_frame->pop_operand();
    int count = op_aux->type_int;
    if (DEBUG) printf("array count %d: %d\n", i, (int) count);

    for (int j = 0; j < (int) count; j++) {
      array_ref->array_type->array->emplace_back(check_string_create_type("["));
    }

    if (DEBUG) cout << "array size " << array_ref->array_type->array->size() << "\n";

    // operand = array_ref->array_type->array[0];

    // array_ref->array_type->array->emplace_back(operand);
    
    if (DEBUG) cout << "--------------------\n";
  }
  
  // for (int i = dimensions; i > 0; i--) {
  //   curr_frame->push_operand(operands[i]);
  // }
  


  curr_frame->push_operand(array_ref);
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
