//
// Created by batis on 16/03/2021.
//

#include <iostream>
#include <vector>
#include "../include/Cp_Info.h"
#include "../include/FileDealer.h"


// Class-------------------------------------------------------------------
Constant_Class::Constant_Class(u1 tag) : Cp_Info(tag) {
    type = CONSTANT_CLASS;
    nameIndex = FileDealer::ReadU2();
}

// Fieldref----------------------------------------------------------------
Constant_Fieldref::Constant_Fieldref(u1 tag) : Cp_Info(tag) {
    type = CONSTANT_FIELDREF;
    classIndex = FileDealer::ReadU2();
    nameAndTypeIndex = FileDealer::ReadU2();
}

// Methodref---------------------------------------------------------------
Constant_Methodref::Constant_Methodref(u1 tag) : Cp_Info(tag) {
    type = CONSTANT_METHODREF;
    classIndex = FileDealer::ReadU2();
    nameAndTypeIndex = FileDealer::ReadU2();
}

// InterfaceMethodref------------------------------------------------------
Constant_InterfaceMethodref::Constant_InterfaceMethodref(u1 tag) : Cp_Info(tag) {
    type = CONSTANT_INTERFACEMETHODREF;
    classIndex = FileDealer::ReadU2();
    nameAndTypeIndex = FileDealer::ReadU2();
}

// String------------------------------------------------------------------
Constant_String::Constant_String(u1 tag) : Cp_Info(tag) {
    type = CONSTANT_STRING;
    stringIndex = FileDealer::ReadU2();
}

// Integer-----------------------------------------------------------------
Constant_Integer::Constant_Integer(u1 tag) : Cp_Info(tag) {
    type = CONSTANT_INTEGER;
    bytes = FileDealer::ReadU4();
}


// Float-------------------------------------------------------------------
Constant_Float::Constant_Float(u1 tag) : Cp_Info(tag) {
    type = CONSTANT_FLOAT;
    bytes = FileDealer::ReadU4();
}


// Long--------------------------------------------------------------------
Constant_Long::Constant_Long(u1 tag) : Cp_Info(tag) {
    type = CONSTANT_LONG;
    bytes[0] = FileDealer::ReadU4();
    bytes[1] = FileDealer::ReadU4();
}

u8 Constant_Long::GetData() {
    u8 aux = (u8)bytes[0] << 32 |  0x00000000ffffffff & bytes[1] ;
    return aux;
}

// Double------------------------------------------------------------------
Constant_Double::Constant_Double(u1 tag) : Cp_Info(tag) {
    type = CONSTANT_DOUBLE;
    bytes[0] = FileDealer::ReadU4();
    bytes[1] = FileDealer::ReadU4();
}

// NameAndType-------------------------------------------------------------
Constant_NameAndType::Constant_NameAndType(u1 tag) : Cp_Info(tag) {
    type = CONSTANT_NAMEANDTYPE;
    nameIndex = FileDealer::ReadU2();
    descriptorIndex  = FileDealer::ReadU2();
}

// UTF8--------------------------------------------------------------------
Constant_Utf8::Constant_Utf8(u1 tag) : Cp_Info(tag) {
    type = CONSTANT_UTF8;
    length = FileDealer::ReadU2();
    bytes = std::vector<u1>(length);
    for(int i = 0;i < length;i++){
        bytes[i] = FileDealer::ReadU1();
    }
}

// MethodHandle------------------------------------------------------------
Constant_MethodHandle::Constant_MethodHandle(u1 tag) : Cp_Info(tag) {
    type = CONSTANT_METHODHANDLE;
    referenceKind = FileDealer::ReadU1();
    referenceIndex = FileDealer::ReadU2();
}

// MethodType--------------------------------------------------------------
Constant_MethodType::Constant_MethodType(u1 tag) : Cp_Info(tag) {
    type = CONSTANT_METHODTYPE;
    descriptorIndex = FileDealer::ReadU2();
}

// InvokeDynamic------------------------------------------------------------
Constant_InvokeDynamic::Constant_InvokeDynamic(u1 tag) : Cp_Info(tag) {
    type = CONSTANT_INVOKEDYNAMIC;
    bootstrapMethodAttrIndex = FileDealer::ReadU2();
    nameAndTypeIndex = FileDealer::ReadU2();
}

