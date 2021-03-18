#include "utils.hpp"

char *intToHex(int integer) {
    char *hex_string;
    hex_string = (char*) malloc(30 * sizeof(char));

    sprintf(hex_string, "%X", integer); //convert number to hex
    std::cout << hex_string << std::endl;
    return hex_string;
}