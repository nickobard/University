// #EX_BEGIN
//
// Created by bardanik on 07/04/23.
//

#include "Bytes.hpp"
// #EX_END


Bytes::Bytes() : bytes(nullptr), len(0) {}

Bytes::~Bytes() {
    free(bytes);
}


bool Bytes::allocateBytes(length l) {
    bytes = (byte *) malloc((len = l));
    if (bytes == nullptr)
        return false;
    return true;
}


char *Bytes::getHexadecimalString(const byte *bytes, length len) {
    length hexLength = 2 * len;
    char *hex = (char *) malloc(hexLength + 1);
    if (hex == nullptr)
        return nullptr;

    for (length i = 0; i < len; i++) {
        byte upper = 0b11110000 & bytes[i];
        byte lower = 0b00001111 & bytes[i];

        hex[i * 2] = lowerToHex(upper >> 4);
        hex[i * 2 + 1] = lowerToHex(lower);
    }
    hex[hexLength] = END_OF_STRING;
    return hex;
}


char Bytes::lowerToHex(byte lower) {
    if (lower < 10)
        return '0' + lower;
    else
        return 'a' + (lower - 10);
}
