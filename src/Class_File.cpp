//
// Created by batis on 16/03/2021.
//

#include "../include/Class_File.h"
#include "../include/FileDealer.h"


Class_File::Class_File(std::string filename)
{

    FileDealer::StartStream(filename);
    if(!FileDealer::on){
        std::cout << "Arquivo não foi aberto" << std::endl;
        exit(1);
    }
    magic = FileDealer::ReadU4();
    if (magic != 0xCAFEBABE)
    {
        std::cout << "Sorry, invalid magic number" << std::endl;
        exit(1);
    }

    minor_version =  FileDealer::ReadU2();
    major_version = FileDealer::ReadU2();
    constant_pool_count = FileDealer::ReadU2();

    if (major_version > 52)
    {
        std::cout << "Wrong .class version" << std::endl;
        exit(1);
    }
    constant_pool = std::vector<std::unique_ptr<Cp_Info>>(constant_pool_count);


    u1 tag;
    for(int i = 1;i < constant_pool_count;i++){
        tag = FileDealer::ReadU1();
        switch (tag) {
            case 7:
                constant_pool[i] = std::unique_ptr<Cp_Info>(new Constant_Class(tag));
                break;
            case 9:
                constant_pool[i] = std::unique_ptr<Cp_Info>(new Constant_Fieldref(tag));
                break;
            case 10:
                constant_pool[i] = std::unique_ptr<Cp_Info>(new Constant_Methodref(tag));
                break;
            case 11:
                constant_pool[i] = std::unique_ptr<Cp_Info>(new Constant_InterfaceMethodref(tag));
                break;
            case 8:
                constant_pool[i] = std::unique_ptr<Cp_Info>(new Constant_String(tag));
                break;
            case 3:
                constant_pool[i] = std::unique_ptr<Cp_Info>(new Constant_Integer(tag));
                break;
            case 4:
                constant_pool[i] = std::unique_ptr<Cp_Info>(new Constant_Float(tag));
                break;
            case 5:
                constant_pool[i] = std::unique_ptr<Cp_Info>(new Constant_Long(tag));
                break;
            case 6:
                constant_pool[i] = std::unique_ptr<Cp_Info>(new Constant_Double(tag));
                break;
            case 12:
                constant_pool[i] = std::unique_ptr<Cp_Info>(new Constant_NameAndType(tag));
                break;
            case 1:
                constant_pool[i] = std::unique_ptr<Cp_Info>(new Constant_Utf8(tag));
                break;
            case 15:
                constant_pool[i] = std::unique_ptr<Cp_Info>(new Constant_MethodHandle(tag));
                break;
            case 16:
                constant_pool[i] = std::unique_ptr<Cp_Info>(new Constant_MethodType(tag));
                break;
            case 18:
                constant_pool[i] = std::unique_ptr<Cp_Info>( new Constant_InvokeDynamic(tag));
                break;
            default:
                std::cout << "Erro na leitura do constant pool no indice " << i << std::endl;
                exit(1);
        }
    }

    access_flags = FileDealer::ReadU2();
    this_class = FileDealer::ReadU2();
    super_class = FileDealer::ReadU2();
    interfaces_count = FileDealer::ReadU2();
    interfaces = std::vector<u2>(interfaces_count);
    for(int i = 0;i < interfaces_count;i++){
        interfaces[i] = FileDealer::ReadU2();
    }
    fields_count = FileDealer::ReadU2();



//    class_file.constant_pool = (Cp_Info *)malloc(sizeof(Cp_Info) * (class_file.constant_pool_count - 1));
    // Minha class_file.constant_pool tem o tamanho necessário, como armazenar cada índice no cpinfo?
    // Preciso ler mais bytes, preciso fazer um reader só para o cp_info?
//    u2 tag = read_1_byte(file);
//    std::cout << "tagname: " << tag << std::endl;

    // u2 class_file.access_flags = read_2_bytes(file);
    // u2 class_file.this_class = read_2_bytes(file);
    // u2 class_file.super_class = read_2_bytes(file);
    // u2 class_file.interfaces_count = read_2_bytes(file);
    // u2 class_file.interfaces = read_2_bytes(file);
    // u2 class_file.fields_count = read_2_bytes(file);
    // u2 class_file.fields = read_2_bytes(file);
    // u2 class_file.methods = read_2_bytes(file);
    // u2 class_file.attributes_count = read_2_bytes(file);
    // u2 class_file.attributes = read_2_bytes(file);
    FileDealer::CloseStream();

    return;
}




std::ostream& operator<<(std::ostream& os, const Class_File& classFile) {
    os << "Magic Numeber: 0x" << std::uppercase << std::hex << classFile.magic << std::endl;
    os << "Minor Version: " << std::dec << classFile.minor_version << std::endl;
    os << "Major Version: " << classFile.major_version << std::endl;
    os << "Constant Pool Count: " << classFile.constant_pool_count << std::endl;
    os << "Constant Pool (Formatar dps):" << std::endl;
    for(int i = 1;i < classFile.constant_pool_count;i++){
        os << "    ConstantPool[" << i << "]: " << (int)classFile.constant_pool[i]->tag << std::endl;
    }

    os << "This Class: " << classFile.this_class << std::endl;
    os << "Super Class: " << classFile.super_class << std::endl;
    os << "Interface Count: " << classFile.interfaces_count << std::endl;
    os << "Interfaces: " << std::endl;
    for(int i = 0;i < classFile.interfaces_count;i++){
        os << "    Interface[" << i <<"]: " << classFile.interfaces[i]<< std::endl;
    }
    os << "Field Count: " << classFile.fields_count << std::endl;

    
    
    //os << "" << std::hex << classFile.magic << std::endl;
    //os << "" << std::hex << classFile.magic << std::endl;
    //os << "" << std::hex << classFile.magic << std::endl;
    //os << "" << std::hex << classFile.magic << std::endl;
    //os << "" << std::hex << classFile.magic << std::endl;

    return os;
}


