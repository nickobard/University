# Hybrid Encryption and Decryption

Your task is to implement two functions (`seal` and `open`) that encrypt and decrypt data using hybrid encryption.

## Parameters of the `seal` Function:

### `bool seal(string_view inFile, string_view outFile, string_view publicKeyFile, string_view symmetricCipher)`

- `inFile` - the file containing the binary data to be encrypted,
- `outFile` - the output file where you will store all the necessary data for decryption,
- `publicKeyFile` - the public key used to encrypt the symmetric key,
- `symmetricCipher` - the name of the symmetric cipher used for encryption.

The return value is `true` in case of success, `false` otherwise. If the function fails, you must ensure that the output file `outFile` does not exist.

The function generates a symmetric (shared) key and an initialization vector (IV) that will be used as input to the symmetric cipher `symmetricCipher`. Using this cipher, key, and IV, you will encrypt the data in `inFile`. The symmetric key will be encrypted using an asymmetric cipher (RSA) with the public key stored in `publicKeyFile`.

OpenSSL will handle most of the work for you:

- `PEM_read_PUBKEY` - reads the public key,
- `EVP_SealInit` - generates the shared key and IV (if needed), encrypts the shared key, and sets the context,
- `EVP_SealUpdate` and `EVP_SealFinal` work the same as in previous tasks.

Hybrid encryption accounts for encryption for multiple recipients. The data is encrypted only once with a single shared key and IV, but the shared key can be encrypted with multiple public keys. Therefore, the function accepts an array of public keys.

The output file will have the following structure:

| Position in File | Length     | Structure         | Description                               |
|------------------|------------|-------------------|-------------------------------------------|
| 0                | 4 B        | int               | NID - numerical identifier for an OpenSSL cipher (used symmetric cipher) |
| 4                | 4 B        | int               | EKlen - length of the encrypted key       |
| 8                | EKlen B    | array of unsigned char | Encrypted key using RSA                   |
| 8 + EKlen        | IVlen B    | array of unsigned char | Initialization vector (if needed)         |
| 8 + EKlen + IVlen| —          | array of unsigned char | Encrypted data                            |

## Parameters of the `open` Function:

### `bool open(string_view inFile, string_view outFile, string_view privateKeyFile)`

- `inFile` - the encrypted file in the same format as the output file from the `seal` function,
- `outFile` - the output file where you will store all the decrypted data (a binary match with the input file to the `seal` function is expected),
- `privateKeyFile` - the private key used to decrypt the encrypted key.

The return value is `true` in case of success, `false` otherwise. If the function fails, you must ensure that the output file `outFile` does not exist.

In this function, the main roles will be played by the functions `PEM_read_PrivateKey`, `EVP_OpenInit`, `EVP_OpenUpdate`, and `EVP_OpenFinal`.

## Sample Data Contents:

- `PublicKey.pem` - public key (try opening it as txt),
- `PrivateKey.pem` - private key,
- `sample.cpp` - file with declarations and basic test,
- `sealed_sample.bin` - encrypted file on which you can test decryption. It was encrypted with the provided public key, and after decryption, you will find ASCII text in it. If you encrypt the same data, the file will not be the same as `sealed_sample.bin` because a different key and IV were used.

## Final Tips:

- There are many places in this task where functions can return an error. Properly check and consider using an object-oriented design and automatic resource release using `unique_ptr` (applies to context, key, allocated arrays, and closing files).
- The length of the encrypted key depends on the public key. You cannot assume a fixed length.
- When compiling, don't forget to link the OpenSSL crypto library using `-lcrypto`.
- The version of OpenSSL on Progtest is 3.0.11.
- All "notes" from the previous task apply.
