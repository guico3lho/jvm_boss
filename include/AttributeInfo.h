//
// Created by batis on 16/03/2021.
//

#ifndef TESTE_ATTRIBUTEINFO_H
#define TESTE_ATTRIBUTEINFO_H

#include "../include/Types.h"

enum ATTRIBUTE_INFO{
    CONSTANTVALUE,
    CODE,
    EXCEPTIONS,
    INNERCLASSES,
    SHYNTETIC,
    GENERIC
};

class Attribute_Info{
public:
    u2 attNameIndex;
    u4 attLength;
    ATTRIBUTE_INFO type;
    ATTRIBUTE_INFO GetType(){
        return type;
    }
    Attribute_Info(u2 nameIndex, u4 length){
        attNameIndex = nameIndex;
        attLength = length;
    }
};

class Attribute_ConstantValue: public Attribute_Info{
public:
    u2 constantValueIndex;
    Attribute_ConstantValue(u2 nameIndex, u4 length) : Attribute_Info(nameIndex, length);
};

class Attribute_Code: public Attribute_Info{
public:
    u2 max_stack;
    u2 max_locals;
    Attribute_Code(u2 nameIndex, u4 length) : Attribute_Info(nameIndex, length);
};



#endif //TESTE_ATTRIBUTEINFO_H
