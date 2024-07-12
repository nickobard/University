#ifndef __PROGTEST__

#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <unistd.h>
#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <cassert>
#include <cstring>

#include <openssl/evp.h>
#include <openssl/rand.h>

using namespace std;

struct crypto_config {
    const char *m_crypto_function;
    std::unique_ptr<uint8_t[]> m_key;
    std::unique_ptr<uint8_t[]> m_IV;
    size_t m_key_len;
    size_t m_IV_len;
};

#endif /* _PROGTEST_ */

using namespace std;

constexpr int BUFFER_SIZE = 1024;
constexpr bool ENCRYPT = true;
constexpr bool DECRYPT = false;
constexpr int IMG_HEADER_SIZE = 18;

using Context = unique_ptr<EVP_CIPHER_CTX, decltype(&EVP_CIPHER_CTX_free)>;

bool valid_secret(unique_ptr<uint8_t[]> &secret, size_t &len, const size_t CIPHERING_LENGTH, bool encryption) {
    if (secret == nullptr || len < CIPHERING_LENGTH) {
        if (!encryption)
            return false;
        auto reset_secret = new uint8_t[CIPHERING_LENGTH];
        if (!RAND_bytes(reset_secret, static_cast<int>(CIPHERING_LENGTH))) {
            delete[] reset_secret;
            return false;
        }
        secret.reset(reset_secret);
        len = CIPHERING_LENGTH;
    }
    return true;
}

bool valid_config(crypto_config &config, const EVP_CIPHER *&cipher, bool is_encryption, bool &requires_IV) {
    OpenSSL_add_all_ciphers();
    cipher = EVP_get_cipherbyname(config.m_crypto_function);
    if (cipher == nullptr)
        return false;

    const int KEY_LENGTH = EVP_CIPHER_key_length(cipher);
    const int IV_LENGTH = EVP_CIPHER_iv_length(cipher);

    if (!valid_secret(config.m_key, config.m_key_len, KEY_LENGTH, is_encryption))
        return false;
    if (!(requires_IV = IV_LENGTH != 0)) // doesn't require IV
        return true;
    if (!valid_secret(config.m_IV, config.m_IV_len, IV_LENGTH, is_encryption))
        return false;

    return true;
}

bool copy_header(ifstream &ifs, ofstream &ofs, size_t file_size) {
    if (file_size < IMG_HEADER_SIZE)
        return false;
    char header_buff[IMG_HEADER_SIZE];

    if (!ifs.read(header_buff, IMG_HEADER_SIZE)
        || !ofs.write(header_buff, IMG_HEADER_SIZE)) {
        return false;
    }
    return true;
}

bool cipher_data(ifstream &ifs, ofstream &ofs, size_t to_read, Context &context) {

    uint8_t in_buffer[BUFFER_SIZE] = {};
    uint8_t out_buffer[BUFFER_SIZE + EVP_MAX_BLOCK_LENGTH] = {};
    int read_bytes = 0;
    int ciphered_bytes = 0;

    while (to_read) {

        if (to_read >= BUFFER_SIZE)
            read_bytes = BUFFER_SIZE;
        else
            read_bytes = static_cast<int>(to_read);

        if (!ifs.read(reinterpret_cast<char *>(&in_buffer), read_bytes))
            return false;

        to_read -= read_bytes;

        if (!EVP_CipherUpdate(context.get(),
                              out_buffer, &ciphered_bytes,
                              in_buffer, read_bytes))
            return false;

        if (!ofs.write(reinterpret_cast<char *>(&out_buffer), ciphered_bytes))
            return false;
    }

    if (!EVP_CipherFinal_ex(context.get(),
                            out_buffer, &ciphered_bytes))
        return false;

    if (!ofs.write(reinterpret_cast<char *>(&out_buffer), ciphered_bytes))
        return false;

    return true;
}

bool cipher(const std::string &in_filename, const std::string &out_filename, crypto_config &config,
            bool is_encryption) {
    const EVP_CIPHER *cipher = nullptr;
    bool requires_IV = false;
    if (!valid_config(config, cipher, is_encryption, requires_IV))
        return false;


    Context context(EVP_CIPHER_CTX_new(), &EVP_CIPHER_CTX_free);
    if (context == nullptr)
        return false;

    // set ios::binary flag to read bytes without translation of characters (i.e. new lines depending on OS type)
    // set ios::ate flag to set file pointer to the end of the file to get file size.
    ifstream ifs(in_filename, ios::binary | ios::in | ios::ate);
    // set ios::trunc to clear content of the file
    ofstream ofs(out_filename, ios::binary | ios::out | ios::trunc);
    if (!ifs.is_open() || !ofs.is_open())
        return false;

    size_t file_size = ifs.tellg(); // get size of the file
    ifs.seekg(0, ios::beg); // set back the file pointer to start

    if (!copy_header(ifs, ofs, file_size)) {
        return false;
    }

    if (!EVP_CipherInit_ex(context.get(),
                           cipher,
                           nullptr,
                           config.m_key.get(),
                           requires_IV ? config.m_IV.get() : nullptr,
                           is_encryption))
        return false;

    return cipher_data(ifs, ofs, file_size - IMG_HEADER_SIZE, context);
}

bool encrypt_data(const std::string &in_filename, const std::string &out_filename, crypto_config &config) {
    return cipher(in_filename, out_filename, config, ENCRYPT);
}

bool decrypt_data(const std::string &in_filename, const std::string &out_filename, crypto_config &config) {
    return cipher(in_filename, out_filename, config, DECRYPT);
}


#ifndef __PROGTEST__

bool compare_files(const char *name1, const char *name2) {
    return true;
}

int main(void) {
    crypto_config config{nullptr, nullptr, nullptr, 0, 0};

    // ECB mode
    config.m_crypto_function = "AES-128-ECB";
    config.m_key = std::make_unique<uint8_t[]>(16);
    memset(config.m_key.get(), 0, 16);
    config.m_key_len = 16;

    assert(encrypt_data("homer-simpson.TGA", "out_file.TGA", config));
    assert(encrypt_data("homer-simpson.TGA", "out_file.TGA", config) &&
           compare_files("out_file.TGA", "homer-simpson_enc_ecb.TGA"));

    assert(decrypt_data("homer-simpson_enc_ecb.TGA", "out_file.TGA", config) &&
           compare_files("out_file.TGA", "homer-simpson.TGA"));

    assert(encrypt_data("UCM8.TGA", "out_file.TGA", config) &&
           compare_files("out_file.TGA", "UCM8_enc_ecb.TGA"));

    assert(decrypt_data("UCM8_enc_ecb.TGA", "out_file.TGA", config) &&
           compare_files("out_file.TGA", "UCM8.TGA"));

    assert(encrypt_data("image_1.TGA", "out_file.TGA", config) &&
           compare_files("out_file.TGA", "ref_1_enc_ecb.TGA"));

    assert(encrypt_data("image_2.TGA", "out_file.TGA", config) &&
           compare_files("out_file.TGA", "ref_2_enc_ecb.TGA"));

    assert(decrypt_data("image_3_enc_ecb.TGA", "out_file.TGA", config) &&
           compare_files("out_file.TGA", "ref_3_dec_ecb.TGA"));

    assert(decrypt_data("image_4_enc_ecb.TGA", "out_file.TGA", config) &&
           compare_files("out_file.TGA", "ref_4_dec_ecb.TGA"));

    // CBC mode
    config.m_crypto_function = "AES-128-CBC";
    config.m_IV = std::make_unique<uint8_t[]>(16);
    config.m_IV_len = 16;
    memset(config.m_IV.get(), 0, 16);

    assert(encrypt_data("UCM8.TGA", "out_file.TGA", config) &&
           compare_files("out_file.TGA", "UCM8_enc_cbc.TGA"));

    assert(decrypt_data("UCM8_enc_cbc.TGA", "out_file.TGA", config) &&
           compare_files("out_file.TGA", "UCM8.TGA"));

    assert(encrypt_data("homer-simpson.TGA", "out_file.TGA", config) &&
           compare_files("out_file.TGA", "homer-simpson_enc_cbc.TGA"));

    assert(decrypt_data("homer-simpson_enc_cbc.TGA", "out_file.TGA", config) &&
           compare_files("out_file.TGA", "homer-simpson.TGA"));

    assert(encrypt_data("image_1.TGA", "out_file.TGA", config) &&
           compare_files("out_file.TGA", "ref_5_enc_cbc.TGA"));

    assert(encrypt_data("image_2.TGA", "out_file.TGA", config) &&
           compare_files("out_file.TGA", "ref_6_enc_cbc.TGA"));

    assert(decrypt_data("image_7_enc_cbc.TGA", "out_file.TGA", config) &&
           compare_files("out_file.TGA", "ref_7_dec_cbc.TGA"));

    assert(decrypt_data("image_8_enc_cbc.TGA", "out_file.TGA", config) &&
           compare_files("out_file.TGA", "ref_8_dec_cbc.TGA"));
    return 0;
}

#endif /* _PROGTEST_ */
