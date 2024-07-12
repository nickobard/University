# File Encryption

Your task is to implement two (or more) functions (not a complete program) that can encrypt and decrypt an image file in TGA format.

For our task, we will consider a simplified form of the image:

- Mandatory header: 18 bytes - these bytes are not modified, just copied into the encrypted image.
- Optional header part: size is calculated from the mandatory part of the header - this part of the header will be considered as image data, i.e., encrypted along with the image data without changes.
- Image data: the rest.

The parameters of the functions you implement are:

### `bool encrypt_data(const string & in_filename, const string & out_filename, crypto_config & config)`

- `in_filename` - input file name,
- `out_filename` - output file name,
- `config` - data structure `crypto_config` described below.

The return value is `true` in case of success, `false` otherwise. Failure occurs if the file is somehow invalid (missing mandatory header, cannot open, read, write, ...) or if the invalid configuration of `crypto_config` cannot be fixed.

### `bool decrypt_data(const string & in_filename, const string & out_filename, crypto_config & config)`

The `decrypt_data` function uses the same interface but performs the inverse operation relative to encryption. It copies the mandatory part of the header, which is not encrypted, and then decrypts the rest of the file in the same way as encryption. In this case, however, we expect the provision of a valid decryption key and IV (if needed). If these parameters are not available, we cannot decrypt the data, and the program should report an error (`return false`).

### `crypto_config` Data Structure

- Chosen block cipher specified by its name,
- Secret encryption key and its size,
- Initialization vector (IV) and its size.

During encryption, the following problem may occur: if the encryption key (or IV) is insufficient (i.e., their length is not at least as large as required by the chosen block cipher or is completely missing), they must be securely generated. If the chosen block cipher does not require an IV (and thus it may not be provided to you), do not generate a new IV! Remember to save any generated keys and IVs in the passed `config` structure!

The following functions for encryption will be useful:

- `EVP_EncryptInit_ex`, or `EVP_DecryptInit_ex`,
- `EVP_EncryptUpdate`, or `EVP_DecryptUpdate`,
- `EVP_EncryptFinal_ex`, or `EVP_DecryptFinal_ex`.

In the OpenSSL documentation, you can see what other functions you could (and should) use. Hint: Isn't there a more general function that would cover these functions?

By default, block ciphers have padding enabled, so the length of the resulting encrypted file may be larger than the original. This is desired (and expected behavior in tests), and you should not change it.

In the test environment, you will be limited not only by time but also by the size of available memory. Your program may be forcibly terminated. Therefore, try not to use the heap unnecessarily or ideally not at all. In 90% of cases, you can get by with just the stack.

Submit a source file containing the implementation of the required `encrypt_data` and `decrypt_data` functions. You can also add other supporting functions that are called from `encrypt_data` and `decrypt_data` to the source file. The function will be called from the test environment, so it is important to strictly follow the specified function interface.

Use the code from the attached archive below as a basis for implementation. The sample contains a test function `main`, and the provided values are used in a basic test. Note that the inclusion of header files and the `main` function are wrapped in a conditional compilation block (#ifdef/#endif). Please keep the conditional compilation blocks in the submitted source file. Conditional compilation will simplify your work. When compiling on your computer, you can normally run and test the program. When compiling on Progtest, the `main` function and the inclusion of header files will "disappear," so it will not collide with the header files and the `main` function of the test environment.
