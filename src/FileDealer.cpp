//
// Created by batis on 15/03/2021.
//
#include <fstream>
#include<string>
#include "../include/FileDealer.h"
#include "../include/Types.h"


std::string FileDealer::fileName;
std::ifstream FileDealer::file;
bool FileDealer::on = false;


int FileDealer::StartStream(std::string nameFile) {
    FileDealer::fileName = nameFile;
    file = std::ifstream(fileName,std::ios::in  | std::ios::binary);
    if(!file){
        std::cout << "Deu erro" << std::endl;
        return 1;
    }
    on = true;
    return 0;
}

void FileDealer::CloseStream(){
    file.close();
}


void FileDealer::ReadAndPrint(){
    printf("\n");
    printf("%llX ",ReadU8());
    printf("\n");
}

u1 FileDealer::ReadU1() {
    char lido[1] = {0};
    file.read(lido,1);
    return (u1)(lido[0]);
}

u2 FileDealer::ReadU2() {
    u1 var1 = FileDealer::ReadU1();
    u1 var2 = FileDealer::ReadU1();
    return ((((u2) var1) << 8) | (CONVERT_U1_MASK & var2));
}

u4 FileDealer::ReadU4() {
    u2 var1 = FileDealer::ReadU2();
    u2 var2 = FileDealer::ReadU2();
    return ((((u4) var1) << 16) | (CONVERT_U2_MASK & var2));
}

u8 FileDealer::ReadU8() {
    u4 var1 = FileDealer::ReadU4();
    u4 var2 = FileDealer::ReadU4();
    return ((((u8) var1) << 32) | (CONVERT_U4_MASK & var2));
}

/*
*/
