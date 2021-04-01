#include "interpreter.hpp"
#include "class_loader.hpp"
#include "instruction.hpp"

std::map<std::string, Class_Loader*> loaded_classes;
std::map<std::string, Class_Loader*> static_classes;
std::string current_path_folder_inter = "test";
std::stack<Frame*> frame_stack;

/**
* @brief Função que executa a interpretação do arquivo .class.
* @param class_file informações do arquivo .class.
* @return void
*/
void execute(Class_File class_file) {

  load_class_memory(class_file);
  std::vector<Instruction> instructions = set_instructions();
  Frame::setup_instructions_func();

  Frame *frame = new Frame(find_main(class_file), class_file);
  frame_stack.push(frame);

  if (DEBUG) std::cout << "INICIA FRAME\n";
  printf("---------------------------------");
  printf("\n\nIniciando Execução\n");
  printf("---------------------------------\n");

  while (!(frame_stack.empty())) {
    frame_stack.top()->execute_frame(); // executa stack frame do topo para baixo
  }

}

/**
 * @brief Carrega outro .class se o arquivo estiver no mesmo diretório.
 * @param c_path nome do próximo arquivo .class a ser carregado
 * @return JavaClass estrutura de dados do arquivo .class a ser carregado
 */
Class_File get_class_info_and_load_not_exists(std::string class_path) {

  Class_Loader *class_loader = static_classes[class_path];

  std::cout << "Procurando .class de nome: " << class_path << std::endl;

  if (class_loader == NULL) {
    // verifica se a classe está no mesmo diretorio atual
    std::string filepath = current_path_folder_inter + class_path + ".class";
    Class_File class_file = read_class_file(filepath);
    class_loader = load_class_memory(class_file);
  }

  return class_loader->class_file;
}

/**
 * @brief Carrega classes para a memória.
 * @param *class_file informações do arquivo .class.
 * @return ClassInstance* ponteiro para instância de uma classe
 */
Class_Loader* load_class_memory(Class_File class_file) {
  // Cp_Info *cp_info = (Cp_Info*) malloc(sizeof(Cp_Info));

  Class_Loader *class_loader = (Class_Loader*) malloc(sizeof(Class_Loader));
  class_loader->class_file = class_file;

  std::string class_name = get_cp_info_utf8(class_file, class_file.this_class);
  class_loader->class_name = &class_name;
  if (DEBUG) std::cout << "Classe estatica " << class_name << " carregada na memoria!\n";

  loaded_classes.insert((std::pair<std::string, Class_Loader*>(class_name, class_loader)));
  static_classes.insert((std::pair<std::string, Class_Loader*>(class_name, class_loader)));

  class_loader->class_fields = new std::map<std::string, Operand*>();
  load_class_var(class_loader);

  if (DEBUG) std::cout << "Classes carregadas na memoria!\n";

  return class_loader;
}

Operand* get_static_field_of_class(std::string class_name, std::string field_name) {
    Class_Loader *class_loader = static_classes.at(class_name);
    if (class_loader != NULL) return class_loader->class_fields->at(field_name);
    return NULL;
}

void push_frame(Frame *frame) {
  frame_stack.push(frame);
}

void pop_frame() {
  frame_stack.pop();
}

Frame* top_frame() {
  Frame *frame = frame_stack.top();
  return frame;
}

/**
 * @brief Retorna a classe estática
 * @param std::string nome da classe a ser retornada a referencia
 * @return ClassInstance* ponteiro da referencia da classe
 */
Class_Loader* get_static_class(std::string class_name){
  return static_classes[class_name];
}