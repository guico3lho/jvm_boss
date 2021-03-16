//
// Created by batis on 15/03/2021.
//

#ifndef TESTE_FILEDEALER_H
#define TESTE_FILEDEALER_H

#include <iostream>
#include <string>
#include<fstream>
#include "../include/Types.h"

#define CONVERT_U1_MASK 0x00ff
#define CONVERT_U2_MASK 0x0000ffff
#define CONVERT_U4_MASK 0x00000000ffffffff



class FileDealer {
    static std::string fileName;
    static std::ifstream file;
public:

    static bool on;
    static int StartStream(std::string nameFile);
    static void CloseStream();
    static void ReadAndPrint();
    static u1 ReadU1();
    static u2 ReadU2();
    static u4 ReadU4();
    static u8 ReadU8();

};




#endif //TESTE_FILEDEALER_H
