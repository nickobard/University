#ifndef __PROGTEST__

#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <cassert>
#include <cstring>

#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/pem.h>

using namespace std;

#endif /* __PROGTEST__ */

using namespace std;

constexpr int BUFFER_SIZE = 1024;
using Context = unique_ptr<EVP_CIPHER_CTX, decltype(&EVP_CIPHER_CTX_free)>;
using PKey = unique_ptr<EVP_PKEY, decltype(&EVP_PKEY_free)>;

bool seal(const char *inFile, const char *outFile, const char *publicKeyFile, const char *symmetricCipher) {
    if (!inFile
        || !outFile
        || !publicKeyFile
        || !symmetricCipher)
        return false;

    auto ifd_pkey = fopen(publicKeyFile, "r");
    if (ifd_pkey == nullptr) {
        return false;
    }
    PKey pkey(PEM_read_PUBKEY(ifd_pkey, nullptr, nullptr, nullptr),
              &EVP_PKEY_free);
    fclose(ifd_pkey);

    if (pkey == nullptr)
        return false;

    OpenSSL_add_all_ciphers();
    const EVP_CIPHER *cipher = EVP_get_cipherbyname(symmetricCipher);
    if (cipher == nullptr)
        return false;

    Context context(EVP_CIPHER_CTX_new(), &EVP_CIPHER_CTX_free);
    if (context == nullptr)
        return false;

    int encrypted_key_size = EVP_PKEY_size(pkey.get());
    auto encrypted_key = unique_ptr<uint8_t, decltype(&free)>((uint8_t *) malloc(encrypted_key_size), &free);
    if (encrypted_key == nullptr)
        return false;

    auto iv = unique_ptr<uint8_t, decltype(&free)>(nullptr, &free);
    const int iv_len = EVP_CIPHER_iv_length(cipher);
    if (iv_len != 0) {
        iv.reset((uint8_t *) malloc(iv_len));
        if (iv == nullptr)
            return false;
    }

    EVP_PKEY *pub_keys[] = {pkey.get()};
    uint8_t *encrypted_keys[] = {encrypted_key.get()};


    if (!EVP_SealInit(context.get(), cipher, encrypted_keys, &encrypted_key_size, iv.get(), pub_keys, 1))
        return false;

    ifstream ifs(inFile, ios::binary | ios::in);
    if (!ifs.is_open())
        return false;

    ofstream ofs(outFile, ios::binary | ios::out | ios::trunc);
    if (!ofs.is_open())
        return false;


    int nid = EVP_CIPHER_nid(cipher);
    if (!ofs.write(reinterpret_cast<char *>(&nid), sizeof(int))
        || !ofs.write(reinterpret_cast<char *>(&encrypted_key_size), sizeof(int))
        || !ofs.write(reinterpret_cast<char *>(encrypted_key.get()), encrypted_key_size)
        || (iv != nullptr && !ofs.write(reinterpret_cast<char *>(iv.get()), iv_len))) {
        remove(outFile);
        return false;
    }

    uint8_t in_buffer[BUFFER_SIZE] = {};
    uint8_t out_buffer[BUFFER_SIZE + EVP_MAX_BLOCK_LENGTH] = {};
    int sealed_bytes = 0;

    while (ifs) {
        ifs.read(reinterpret_cast<char *>(in_buffer), BUFFER_SIZE);
        auto read_bytes = ifs.gcount();
        if (!EVP_SealUpdate(context.get(), out_buffer, &sealed_bytes, in_buffer, read_bytes)) {
            remove(outFile);
            return false;
        }
        if (!ofs.write(reinterpret_cast<char *>(out_buffer), sealed_bytes)) {
            remove(outFile);
            return false;
        }
    }
    if (!ifs.eof()) {
        remove(outFile);
        return false;
    }

    sealed_bytes = 0;

    if (!EVP_SealFinal(context.get(), out_buffer, &sealed_bytes)) {
        remove(outFile);
        return false;
    }
    if (!ofs.write(reinterpret_cast<char *>(out_buffer), sealed_bytes)) {
        remove(outFile);
        return false;
    }
    return true;
}


bool open(const char *inFile, const char *outFile, const char *privateKeyFile) {
    if (!inFile
        || !outFile
        || !privateKeyFile)
        return false;

    auto ifd_pkey = fopen(privateKeyFile, "r");
    if (ifd_pkey == nullptr) {
        return false;
    }
    PKey pkey(PEM_read_PrivateKey(ifd_pkey, nullptr, nullptr, nullptr),
              &EVP_PKEY_free);
    fclose(ifd_pkey);

    if (pkey == nullptr)
        return false;

    ifstream ifs(inFile, ios::binary | ios::in);

    if (!ifs.is_open())
        return false;

    int nid = 0;
    int encrypted_key_size = 0;
    if (!ifs.read(reinterpret_cast<char *>(&nid), sizeof(int))
        || !ifs.read(reinterpret_cast<char *>(&encrypted_key_size), sizeof(int)))
        return false;
    auto encrypted_key = unique_ptr<uint8_t, decltype(&free)>((uint8_t *) malloc(encrypted_key_size), &free);

    if (encrypted_key == nullptr)
        return false;

    if (!ifs.read(reinterpret_cast<char *>(encrypted_key.get()), encrypted_key_size))
        return false;

    auto cipher = EVP_get_cipherbynid(nid);
    if (cipher == nullptr) {
        return false;
    }

    Context context(EVP_CIPHER_CTX_new(), &EVP_CIPHER_CTX_free);
    if (context == nullptr)
        return false;

    auto iv = unique_ptr<uint8_t, decltype(&free)>(nullptr, &free);
    const int iv_len = EVP_CIPHER_iv_length(cipher);
    if (iv_len != 0) {
        iv.reset((uint8_t *) malloc(iv_len));
        if (iv == nullptr)
            return false;
        if (!ifs.read(reinterpret_cast<char *>(iv.get()), iv_len))
            return false;
    }

    if (!EVP_OpenInit(context.get(), cipher, encrypted_key.get(), encrypted_key_size, iv.get(), pkey.get()))
        return false;

    ofstream ofs(outFile, ios::binary | ios::out | ios::trunc);
    if (!ofs.is_open())
        return false;

    uint8_t in_buffer[BUFFER_SIZE] = {};
    uint8_t out_buffer[BUFFER_SIZE + EVP_MAX_BLOCK_LENGTH] = {};
    int opened_bytes = 0;


    while (ifs) {
        ifs.read(reinterpret_cast<char *>(in_buffer), BUFFER_SIZE);
        auto read_bytes = ifs.gcount();
        if (!EVP_OpenUpdate(context.get(), out_buffer, &opened_bytes, in_buffer, read_bytes)) {
            remove(outFile);
            return false;
        }
        if (!ofs.write(reinterpret_cast<char *>(out_buffer), opened_bytes)) {
            remove(outFile);
            return false;
        }
    }
    if (!ifs.eof()) {
        remove(outFile);
        return false;
    }

    opened_bytes = 0;

    if (!EVP_OpenFinal(context.get(), out_buffer, &opened_bytes)) {
        remove(outFile);
        return false;
    }
    if (!ofs.write(reinterpret_cast<char *>(out_buffer), opened_bytes)) {
        remove(outFile);
        return false;
    }

    return true;
}


#ifndef __PROGTEST__

int main(void) {
    assert(seal("fileToEncrypt", "sealed.bin", "PublicKey.pem", "aes-128-cbc"));
    assert(open("sealed.bin", "openedFileToEncrypt", "PrivateKey.pem"));

    assert(open("sealed_sample.bin", "opened_sample.txt", "PrivateKey.pem"));

    return 0;
}

#endif /* __PROGTEST__ */

