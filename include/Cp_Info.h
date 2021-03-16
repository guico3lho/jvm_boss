//
// Created by batis on 16/03/2021.
//

#ifndef TESTE_CP_INFO_H
#define TESTE_CP_INFO_H
#include "../include/Types.h"

enum CP_INFO{
    CONSTANT_CLASS,
    CONSTANT_FIELDREF,
    CONSTANT_METHODREF,
    CONSTANT_INTERFACEMETHODREF,
    CONSTANT_STRING,
    CONSTANT_INTEGER,
    CONSTANT_FLOAT,
    CONSTANT_LONG,
    CONSTANT_DOUBLE,
    CONSTANT_NAMEANDTYPE,
    CONSTANT_UTF8,
    CONSTANT_METHODHANDLE,
    CONSTANT_METHODTYPE,
    CONSTANT_INVOKEDYNAMIC,
};

class Cp_Info{
public:
    u1 tag;
    CP_INFO type;
    CP_INFO GetType(){
        return type;
    }
    Cp_Info(u1 tag) {
        this->tag = tag;
    }
};


class Constant_Class: public Cp_Info{
public:
    Constant_Class(u1 tag);
    u2 nameIndex;
};

class Constant_Fieldref: public Cp_Info{
public:
    Constant_Fieldref(u1 tag);
    u2 classIndex;
    u2 nameAndTypeIndex;
};

class Constant_Methodref: public Cp_Info{
public:
    Constant_Methodref(u1 tag);
    u2 classIndex;
    u2 nameAndTypeIndex;

};

class Constant_InterfaceMethodref: public Cp_Info{
public:
    Constant_InterfaceMethodref(u1 tag);
    u2 classIndex;
    u2 nameAndTypeIndex;
};

class Constant_String: public Cp_Info{
public:
    Constant_String(u1 tag);
    u2 stringIndex;
};

class Constant_Integer: public Cp_Info{
public:
    Constant_Integer(u1 tag);
    u4 bytes;
};

class Constant_Float: public Cp_Info{
public:
    Constant_Float(u1 tag);
    u4 bytes;
};

class Constant_Long: public Cp_Info {
public:
    Constant_Long(u1 tag);
    u4 bytes[2];
    u8 GetData();
};

class Constant_Double: public Cp_Info{
public:
    Constant_Double(u1 tag);
    u4 bytes[2];
};

class Constant_NameAndType: public Cp_Info{
public:
    Constant_NameAndType(u1 tag);
    u2 nameIndex;
    u2 descriptorIndex;
};

class Constant_Utf8: public Cp_Info{
public:
    Constant_Utf8(u1 tag);
    u2 length;
    std::vector<u1> bytes;
};

class Constant_MethodHandle: public Cp_Info{
public:
    Constant_MethodHandle(u1 tag);
    u1 referenceKind;
    u2 referenceIndex;
};

class Constant_MethodType: public Cp_Info{
public:
    Constant_MethodType(u1 tag);
    u2 descriptorIndex;
};

class Constant_InvokeDynamic: public Cp_Info{
public:
    Constant_InvokeDynamic(u1 tag);
    u2 bootstrapMethodAttrIndex;
    u2 nameAndTypeIndex;
};

#endif //TESTE_CP_INFO_H
