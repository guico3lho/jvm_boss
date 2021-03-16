//
// Created by batis on 16/03/2021.
//

#ifndef TESTE_CLASS_FILE_H
#define TESTE_CLASS_FILE_H


#include <iostream>
#include <vector>
#include <memory>
#include "Types.h"
#include "../include/Cp_Info.h"

class Class_File
{
public:
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    std::vector<std::unique_ptr<Cp_Info>> constant_pool;

    u2 access_flags;
    u2 this_class;
    u2 super_class;
    u2 interfaces_count;
    std::vector<u2> interfaces;
    u2 fields_count;
    // Field_Info * fields;
    // u2 methods_count;
    // Method_Info * methods;
    // u2 attributes_count;
    // Attribute_Info * attributes;

    Class_File(std::string filename);
    friend std::ostream& operator<<(std::ostream& os, const Class_File& cr);
};

#endif //TESTE_CLASS_FILE_H
