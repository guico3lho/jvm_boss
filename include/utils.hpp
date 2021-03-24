#ifndef __UTILS__
#define __UTILS__

#include "types.hpp"
#include "read_bytes.hpp"

// Define usada pelo dev para printar o nome da variável e seu valor
#define LOG(a)                                           \
    do                                                    \
    {                                                     \
        std::cout << #a ": " << (a) << std::endl; \
    } while (false)

// Define usado para printar algo pro usuário do sistema.
#define PRINT(a)                                           \
    do                                                    \
    {                                                     \
        std::cout  << (a) << std::endl; \
    } while (false)

char * intToHex(int inteiro);


#endif 
