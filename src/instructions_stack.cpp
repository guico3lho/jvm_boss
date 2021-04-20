/** @file instructions_stack.cpp
 *  @brief Módulo que contém as instruções de opcode do tipo stack da JVM.
 *  @bug No know bugs.
 */
#include "interpreter.hpp"


/*************************** STACK ***************************/

void pop(Frame *curr_frame) {
  curr_frame->pc++;
  curr_frame->pop_operand();
}

void pop2(Frame *curr_frame) {
  curr_frame->pc++;
  Operand *operand = curr_frame->pop_operand();

  if (operand->tag != CONSTANT_LONG && operand->tag != CONSTANT_DOUBLE)
    curr_frame->pop_operand();
}

/**
 * @brief Faz uma cópia do item que está no topo da pilha e o adiciona ao
 *  topo da pilha.
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void dup(Frame *curr_frame) {
  curr_frame->pc++;

  Operand *copy_1 = copy_operand(curr_frame->operand_stack.top());

  if (DEBUG) cout << "top array size "
                      << copy_1->array_type->array->size()
                      << "\n";

  curr_frame->push_operand(copy_1);

  if (DEBUG) cout << "dup\n";
}

/**
 * @brief Duplica o item no topo da pilha e pusha depois do segundo elemento da pilha.
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void dup_x1(Frame *curr_frame) {
    curr_frame->pc++;
    Operand *value = curr_frame->pop_operand();
    Operand *value2 = curr_frame->pop_operand();
    if (
      value->tag == CONSTANT_DOUBLE || value->tag == CONSTANT_LONG || 
      value2->tag == CONSTANT_DOUBLE || value2->tag == CONSTANT_LONG
    ) {
        curr_frame->push_operand(value2);
        curr_frame->push_operand(value);
    } else {
        Operand *tipo = copy_operand(value);
        curr_frame->push_operand(tipo);
        curr_frame->push_operand(value2);
        curr_frame->push_operand(value);
    }
}

/**
 * @brief Duplica o item no topo da pilha e pusha depois do terceiro elemento da pilha
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void dup_x2(Frame *curr_frame) {
    curr_frame->pc++;
    Operand* value = curr_frame->pop_operand();
    Operand* value2 = curr_frame->pop_operand();

    if (value->tag != CONSTANT_DOUBLE && value->tag != CONSTANT_LONG) {
        if (value2->tag == CONSTANT_DOUBLE || value2->tag == CONSTANT_LONG) {
            Operand* tipo = copy_operand(value);
            curr_frame->push_operand(tipo);
            curr_frame->push_operand(value2);
            curr_frame->push_operand(value);

        }
        else {
            Operand* value3 = curr_frame->pop_operand();
            if (value3->tag != CONSTANT_DOUBLE && value3->tag != CONSTANT_LONG) {
                Operand* tipo = copy_operand(value);
                curr_frame->push_operand(tipo);
                curr_frame->push_operand(value3);
                curr_frame->push_operand(value2);
                curr_frame->push_operand(value);
            }
        }
    }
}

/**
 * @brief Faz uma cópia de dois itens que estao no topo da pilha e o(s) adiciona ao topo da pilha.
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void dup2(Frame *curr_frame) {
    curr_frame->pc++;
    Operand *value1 = curr_frame->pop_operand();
    if (value1->tag != CONSTANT_DOUBLE && value1->tag != CONSTANT_LONG) {
        Operand *value2 = curr_frame->pop_operand();

        Operand *tipo1 = copy_operand(value1);
        Operand *tipo2 = copy_operand(value2);

        curr_frame->push_operand(tipo2);
        curr_frame->push_operand(tipo1);

        curr_frame->push_operand(value2);
        curr_frame->push_operand(value1);

    } else {
        Operand *tipo = copy_operand(value1);
        curr_frame->push_operand(tipo);
        curr_frame->push_operand(value1);
    }
}

/**
 * @brief Duplica um ou dois valores da pilha de operandos e insere os valores duplicados na ordem original
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void dup2_x1(Frame *curr_frame) {
    curr_frame->pc++;
    Operand *value1 = curr_frame->pop_operand();
    Operand *value2 = curr_frame->pop_operand();

    if (value1->tag != CONSTANT_DOUBLE && value1->tag != CONSTANT_LONG) {
        Operand* value3 = curr_frame->pop_operand();

        Operand *tipo1 = copy_operand(value1);
        Operand *tipo2 = copy_operand(value2);

        curr_frame->push_operand(tipo2);
        curr_frame->push_operand(tipo1);

        curr_frame->push_operand(value3);

        curr_frame->push_operand(value2);
        curr_frame->push_operand(value1);
    } else {
        Operand* tipo1 = copy_operand(value1);

        curr_frame->push_operand(tipo1);
        curr_frame->push_operand(value2);
        curr_frame->push_operand(value1);
    }
}

/**
 * @brief Duplica um ou dois operandos da pilha e insere os valores duplicados na ordem original
 * @param *curr_frame ponteiro para o frame atual
 * @return void
 */
void dup2_x2(Frame *curr_frame) {
    curr_frame->pc++;
    Operand* value1 = curr_frame->pop_operand();
    Operand* value2 = curr_frame->pop_operand();

    Operand* tipo1 = copy_operand(value1);
    if (value1->tag != CONSTANT_DOUBLE && value1->tag != CONSTANT_LONG && value2->tag != CONSTANT_DOUBLE && value2->tag != CONSTANT_LONG) {
        Operand* value3 = curr_frame->pop_operand();
        Operand* tipo2 = copy_operand(value2);

        if (value3->tag != CONSTANT_DOUBLE && value3->tag != CONSTANT_LONG) {
            Operand* value4 = curr_frame->pop_operand();

            curr_frame->push_operand(tipo2);
            curr_frame->push_operand(tipo1);

            curr_frame->push_operand(value4);
            curr_frame->push_operand(value3);

            curr_frame->push_operand(value2);
            curr_frame->push_operand(value1);
        } else {
            curr_frame->push_operand(tipo2);
            curr_frame->push_operand(tipo1);

            curr_frame->push_operand(value3);
            curr_frame->push_operand(value2);
            curr_frame->push_operand(value1);
        }
    }
    else {
        if (value2->tag == CONSTANT_DOUBLE || value2->tag == CONSTANT_LONG) {
            curr_frame->push_operand(tipo1);
            curr_frame->push_operand(value2);
            curr_frame->push_operand(value1);
        }
        else {
            Operand* value3 = curr_frame->pop_operand();

            curr_frame->push_operand(tipo1);
            curr_frame->push_operand(value3);
            curr_frame->push_operand(value2);
            curr_frame->push_operand(value1);
        }
    }
}

void swap(Frame *curr_frame) {
  curr_frame->pc++;

  Operand *operand_1 = curr_frame->pop_operand();
  Operand *operand_2 = curr_frame->pop_operand();

  curr_frame->push_operand(operand_1);
  curr_frame->push_operand(operand_2);
}

