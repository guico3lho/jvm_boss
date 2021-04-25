/** 
 *  @file read_bytes.hpp
 *  @brief Estruturas e declarações das funções para ler bytes.
 */

#ifndef __READ_BYTES_H__
#define __READ_BYTES_H__

#include <cstdint>
#include <iostream>
#include "types.hpp"

u1 read_1_byte(FILE* fp);
u2 read_2_bytes(FILE* fp);
u4 read_4_bytes(FILE* fp);

#endif