// #EX_BEGIN
//
// Created by bardanik on 07/04/23.
//

#include "Hasher.hpp"
// #EX_END


Hasher::Hasher() : context(nullptr), type(nullptr) {}


Hasher::~Hasher() {
    if (context != nullptr)
        EVP_MD_CTX_free(context);
}


bool Hasher::init(int bitsToCheck, const char *function) {
    OpenSSL_add_all_digests();
    return (type = EVP_get_digestbyname(function))
           && (context = EVP_MD_CTX_new())
           && (bits = bitsToCheck) <= (int)(hash.len = EVP_MD_size(type)) * 8
           && hash.allocateBytes(hash.len)
           && RAND_bytes(message, messageLength);
}

bool Hasher::calculateHash() {
    return EVP_DigestInit(context, type)
           && EVP_DigestUpdate(context, message, messageLength)
           && EVP_DigestFinal_ex(context, hash.bytes, &hash.len);
}


bool Hasher::findHashWithZeroBits(length pos) {
    if (pos >= messageLength) {
        if (!calculateHash())
            throw std::runtime_error("Error: Could not calculate hash");
        return checkHashBytes();
    }

    for (length j = 0; j <= BYTE_MAX; j++) {
        if (findHashWithZeroBits(pos + 1)) {
            return true;
        }
        message[pos]++;
    }
    return false;
}


int findHashEx(int bits, char **message, char **hash, const char *hashFunction) {
    if (bits < 0)
        return false;

    auto hs = Hasher();
    if (!hs.init(bits, hashFunction))
        return false;

    try {
        if (!hs.findHashWithZeroBits(bits))
            return false;
    } catch (std::runtime_error &e) {
        return false;
    }

    *message = Bytes::getHexadecimalString(hs.message, hs.messageLength);
    *hash = Bytes::getHexadecimalString(hs.hash.bytes, hs.hash.len);
    return true;
}

int findHash(int bits, char **message, char **hash) {
    return findHashEx(bits, message, hash, "sha512");
}


bool Hasher::checkHashBytes() {
    int byteOffset = bits / 8;
    for (int i = 0; i < byteOffset; i++) {
        if (hash.bytes[i] != 0)
            return false;
    }
    int bitOffset = bits % 8;
    byte inspectedByte = hash.bytes[byteOffset];
    switch (bitOffset) {
        case 0:
            return true;
        case 1:
            if (0b10000000 > inspectedByte)
                return true;
            break;
        case 2:
            if (0b01000000 > inspectedByte)
                return true;
            break;
        case 3:
            if (0b00100000 > inspectedByte)
                return true;
            break;
        case 4:
            if (0b00010000 > inspectedByte)
                return true;
            break;
        case 5:
            if (0b00001000 > inspectedByte)
                return true;
            break;
        case 6:
            if (0b00000100 > inspectedByte)
                return true;
            break;
        case 7:
            if (0b00000010 > inspectedByte)
                return true;
            break;
    }
    return false;
}


#ifndef __PROGTEST__

int checkHash(int bits, char *hexString) {
    int hexOffset = bits / 4;
    for (int i = 0; i < hexOffset; i++) {
        if (hexString[i] != '0')
            return false;
    }
    int hexBitOffset = bits % 4;
    char inspectedHex = hexString[hexOffset];
    switch (hexBitOffset) {
        case 0:
            return true;
        case 1:
            if ('8' > inspectedHex)
                return true;
            break;
        case 2:
            if ('4' > inspectedHex)
                return true;
            break;
        case 3:
            if ('2' > inspectedHex)
                return true;
            break;
    }
    return false;
}

#endif /* __PROGTEST__ */

