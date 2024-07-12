## Array Rotation

The task is to implement a function (not the entire program, just the function) that performs a cyclic rotation of the contents of an array.

The function has the following interface:

```c
void rotateArray(int array[], int arrayLen, int rotateBy);
```

- array is an input-output parameter. It refers to the array whose elements are to be rotated,
- arrayLen indicates the number of elements in the array being processed,
- rotateBy determines the size of the shift. A value of 0 means leaving the array unchanged. A positive value shifts elements towards the end of the array, while a negative value shifts them towards the beginning. For example, for rotateBy=2, array[0] moves to array[2], array[1] to array[3], ..., array[arrayLength - 2] to array[0] and array[arrayLength-1] to array[1].
- The function must be reasonably efficient, especially in terms of memory demands. The function must not allocate a copy of the input array, as it will not have enough memory available (memory for a few integer variables is available).


A sample usage of the function is included in the attached archive.

Notes:

- Use the source code from the attached file as the basis for your solution.
- You can add more of your tests to the main function, or you can change it freely. It is important to maintain conditional compilation.
- The example uses the assert macro. If the parameter is a non-zero value, the macro does nothing. If the parameter is false (zero), the macro terminates the program and prints the line where the failure occurred. Therefore, if your implementation passes the example tests, the program will run and display nothing.
- Available header files can be seen in the attached pattern. Other header files are not available and are not needed. Do not insert additional header files using #include, as the program will end with a compilation error.


In the attached source code, two functions are missing: rotateArray and identicalArrays. The latter mentioned function is a helper, comparing the contents of arrays in automated tests. It is assumed that you will implement both functions, but only the rotateArray function will be tested.
During the tests, memory demands are checked. If you allocate too much memory, the memory requirements test will fail.
In the basic implementation, it may be appropriate to differentiate shifts with positive and negative rotateBy values.
To pass the bonus test, a memory and time-efficient algorithm is required. A naive (quadratic) algorithm will pass all tests except the bonus test. To pass the bonus test, a linear algorithm is necessary.
