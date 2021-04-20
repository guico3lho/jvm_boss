/** @file instructions_extended.cpp
 *  @brief Módulo que contém as instruções tipo extendidas da JVM.
 *  @bug No know bugs.
 */
#include "interpreter.hpp"

/*************************** EXTENDED ***************************/

void ifnull(Frame *curr_frame) {
    Operand *operand = curr_frame->pop_operand();

    if (!(operand->type_int)) {
        int shift;
        shift = curr_frame->method_code->code[curr_frame->pc + 1];
        shift = (shift << 8 ) | curr_frame->method_code->code[curr_frame->pc + 2];
        curr_frame->pc += shift;
    } else {
        curr_frame->pc +=3;
    }
}

void ifnonnull(Frame *curr_frame) {
    Operand *operand = curr_frame->pop_operand();

    if (operand->type_int) {
        int shift;
        shift = curr_frame->method_code->code[curr_frame->pc + 1];
        shift = (shift << 8 ) | curr_frame->method_code->code[curr_frame->pc + 2];
        curr_frame->pc += shift;
    } else {
        curr_frame->pc +=3;
    }
}
