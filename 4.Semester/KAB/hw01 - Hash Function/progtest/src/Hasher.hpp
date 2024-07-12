// #PRIOR_2
// #EX_BEGIN
//
// Created by bardanik on 07/04/23.
//

#ifndef PROGTEST_HASHER_HPP
#define PROGTEST_HASHER_HPP


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

#include "Bytes.hpp"

// #EX_END

constexpr length RAND_MESSAGE_SIZE = 64;

struct Hasher {
    Hasher();

    ~Hasher();

    bool init(int bitsToCheck, const char *function = "sha512" );

    bool calculateHash();

    bool findHashWithZeroBits(length pos = 0);

    bool checkHashBytes();

    byte message[RAND_MESSAGE_SIZE];
    length messageLength = sizeof(message);

    Bytes hash;
    int bits;

    EVP_MD_CTX *context;
    const EVP_MD *type;

};

int findHashTimeMeasure(int bits);

int findHash(int bits, char **message, char **hash);

int findHashEx(int bits, char **message, char **hash, const char *hashFunction);

int checkHash(int bits, char *hexString);

// #EX_BEGIN
#endif //PROGTEST_HASHER_HPP
// #EX_END

