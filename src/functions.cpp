#include "../include/functions.hpp"


char *intToHex(int inteiro)
{   
    char *hex_string;
    hex_string = (char *)malloc(sizeof(30 * sizeof(char)));

    sprintf(hex_string, "%X", inteiro); //convert number to hex

    return hex_string;
}