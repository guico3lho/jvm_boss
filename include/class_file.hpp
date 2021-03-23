 #pragma once
#ifndef __CLASS_FILE__
#define __CLASS_FILE__
#endif // !
#include <iostream>
#include <types.hpp>
#include "read_bytes.hpp"
#include "functions.hpp"

class Cp_Info;

class Class_File
{
    public:
        u4 magic;
        u2 minor_version;
        u2 major_version;
        u2 constant_pool_count;
        Cp_Info * constant_pool;
        //constant_pool->cp_info_reader()
        u2 access_flags;
        u2 this_class;
        u2 super_class;
        // u2 interfaces_count;
        // u2 * interfaces;
        // u2 fields_count;
        // Field_Info * fields;
        // u2 methods_count;
        // Method_Info * methods;
        // u2 attributes_count;
        // Attribute_Info * attributes;
        
};