/**
 *  @file interpreter.cpp
 *  @brief Arquivo com funções para a execução do bytecode (.class)
 */

#include "interpreter.hpp"

std::stack<Frame*> frame_stack;


/**
* @brief Função que executa a interpretação do arquivo .class.
* @param class_file estrutura class_file de onde os frames serão criados
* @return void
*/
void execute(Class_File class_file) {

  Method_Area * method_area = new Method_Area();
  method_area = load_class_memory(class_file);
  // std::vector<Instruction> instructions = set_instructions();
  //NOTE: Revisado até aqui
  Frame::setup_instructions_func();// preenche vetor de instruções func

  if (DEBUG) std::cout << "INICIA FRAME\n";
  Frame *frame = new Frame(find_main(method_area), class_file);
  frame_stack.push(frame);

  printf("\n----------Iniciando Execucao----------\n");

  while (!(frame_stack.empty())) {
    frame_stack.top()->execute_frame(); // executa stack frame do topo para baixo
  }
}

/** 
 * @brief Coloca um frame da pilha de frames.
 * @param frame ponteiro para o frame que será colocado na pilha.
 * @return void
 */
void push_frame(Frame *frame) {
  frame_stack.push(frame);
}

/** 
 * @brief Retira um frame da pilha de frames.
 * @param void
 * @return void
 */
void pop_frame() {
  frame_stack.pop();
}

/** 
 * @brief Returna o frame no inicio da pilha.
 * @param void.
 * @return um ponteiro para o frame
 */
Frame* top_frame() {
  return frame_stack.top();
}

u2 get_method_code_index(Frame* curr_frame) {
  u2 index = curr_frame->method_code->code[curr_frame->pc++];
  index = (index << 8) + curr_frame->method_code->code[curr_frame->pc++];
  return index;
}