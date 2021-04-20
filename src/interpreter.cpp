/**
 *  @file interpreter.cpp
 *  @brief Arquivo com funções para a execução do bytecode (.class)
 */

#include "interpreter.hpp"

std::stack<Frame*> frame_stack;

/**
* @brief Função que executa a interpretação do arquivo .class.
*/
void execute(Class_File class_file) {

  load_class_memory(class_file);
  // std::vector<Instruction> instructions = set_instructions();
  Frame::setup_instructions_func();

  if (DEBUG) std::cout << "INICIA FRAME\n";
  Frame *frame = new Frame(find_main(class_file), class_file);
  frame_stack.push(frame);

  printf("\n----------Iniciando Execucao----------\n");

  while (!(frame_stack.empty())) {
    frame_stack.top()->execute_frame(); // executa stack frame do topo para baixo
  }
}

void push_frame(Frame *frame) {
  frame_stack.push(frame);
}

void pop_frame() {
  frame_stack.pop();
}

Frame* top_frame() {
  return frame_stack.top();
}