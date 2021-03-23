#ifndef __CLASS_FILE_READER__
#define __CLASS_FILE_READER__
#endif // !

#include "cp_info.hpp"
#include "class_file.hpp"

class Class_File_Reader{
public:
    Cp_Info * cp_info = new Cp_Info();


    Class_File read_class_file(std::string file_name);
};