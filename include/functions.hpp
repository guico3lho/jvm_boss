#ifndef __FUNTIONS__
#define __FUNTIONS__

#endif // !
#include <iostream>
#include <fstream>
#include "types.hpp"
#include "read_bytes.hpp"
// Similar to Utils.hpp
#define LOG(a)                                           \
    do                                                    \
    {                                                     \
        std::cout << #a ": " << (a) << std::endl; \
    } while (false)
// Define usada pelo dev para printar o nome da variável e seu valor
// Coloque como parâmetro 1 unico argumento por vez

#define PRINT(a)                                           \
    do                                                    \
    {                                                     \
        std::cout  << (a) << std::endl; \
    } while (false)
// Define usado para printar algo pro usuário do sistema.
// Coloque como parâmetro 1 unico argumento por vez


char * intToHex(int inteiro);



    
