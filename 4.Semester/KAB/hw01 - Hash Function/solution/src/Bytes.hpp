
// #PRIOR_1
// #EX_BEGIN
//
// Created by bardanik on 07/04/23.
//

#ifndef PROGTEST_BYTES_HPP
#define PROGTEST_BYTES_HPP

#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include <openssl/evp.h>
#include <openssl/rand.h>

// #EX_END


using std::cout, std::endl, std::flush, std::hex;

using byte = unsigned char;
using length = unsigned int;

constexpr byte END_OF_STRING = '\0';
constexpr byte BYTE_MAX = UCHAR_MAX;


struct Bytes {
    Bytes();

    ~Bytes();

    static char *getHexadecimalString(const byte *bytes, length len);

    static char lowerToHex(byte lower);

    bool allocateBytes(length l);

    byte *bytes;
    length len;

};

// #EX_BEGIN
#endif //PROGTEST_BYTES_HPP
// #EX_END


