#include "interpreter.hpp"


void execute(Class_File class_file)
{
    std::cout << "Chamou função execute" << std::endl;
    load_class_memory(class_file); // Class Loader
    std::vector<Instruction> instructions = set_instructions();
    // Frame::setup_instructions_func();
}

