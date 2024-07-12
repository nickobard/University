### Code Structure:

```text
.
├── graph.ipynb
├── graph.nb
├── python_data.txt
├── README.md
├── solution
│   ├── CMakeLists.txt
│   ├── main.cpp
│   └── src
│       ├── Bytes.cpp
│       ├── Bytes.hpp
│       ├── Hasher.cpp
│       └── Hasher.hpp
└── wolfram_data.txt

2 directories, 11 files
```

# Hash Function

Your task is to implement a function (or a set of functions, not a complete program) that will find any message whose hash (SHA-512) starts with a sequence of zero bits from the left.

The bit order is big-endian: Byte 0 from MSB to LSB, Byte 1 from MSB to LSB, ..., the last byte from MSB to LSB.

In other words, two zero bits correspond, for example, to the byte 0010 0111 (0x27).

The function is required in two variants:

- Basic solution (`findHash`). The implementation of this function is mandatory.
- Enhanced solution (`findHashEx`). The implementation of this function is not mandatory, but without a provided "dummy" implementation, the task will not compile. Implement the function if you decide to strive for a bonus.

The parameters of the functions you implement are:

### `int findHash (int bits, string & message, string & hash)`

- `bits` - the required number of zero bits in the hash of the message.
- `message` - output parameter. This parameter contains the data for which the corresponding hash was found. The result is stored as a hexadecimal string.
- `hash` - output parameter. This is the hash of the `message` from the previous parameter, again as a hexadecimal string.

The return value of the function is 1 in case of success, 0 in case of failure or incorrect parameters. These typically include a requested number of zero bits that does not make sense.

### `int findHashEx (int bits, string & message, string & hash, string_view hashFunction)`

- An extension of the `findHash` function. All parameters and the return value remain the same as in the basic variant.
- `hashFunction` - a new parameter specifying which hash function should be used to find the sequence of zero bits. The given hash function name is compatible with the `EVP_get_digestbyname` function.

Submit a source file that contains the implementation of the required function `findHash` or `findHashEx`. You can also add other supporting functions that are called from `findHash` (or `findHashEx`) to the source file. The function will be called from the test environment, so it is important to strictly follow the specified function interface.

Use the code from the attached archive below as a basis for implementation. The sample contains a test function `main`, and the provided values are used in a basic test. Note that the inclusion of header files and the `main` function are wrapped in a conditional compilation block (#ifdef/#endif). Please keep the conditional compilation blocks in the submitted source file. Conditional compilation will simplify your work. When compiling on your computer, you can normally run and test the program. When compiling on Progtest, the `main` function and the inclusion of header files will "disappear," so it will not collide with the header files and the `main` function of the test environment.

The sample also contains a `dumpMatch` function, which you will (most likely) need to implement for your local testing. The function is wrapped in a conditional compilation block (it will not be tested). However, it is advisable to implement it to verify the correctness of your solu
