## Average of 3

The task is to implement a function (not the entire program, just the function) that calculates the average of 3 integers.

The function has the following interface:

```c
long long avg3(long long a, long long b, long long c);
```

- The input parameters of the function are three numbers, the function will calculate their average.
- The return value of the function is the calculated average value.
- If the average is not an integer, the function discards the decimal part (rounding towards 0).
- The function cannot fail; the average is defined for any trio of input numbers.

Example of function usage:

```c
assert(avg3(1, 2, 3) == 2);
assert(avg3(-100, 100, 30) == 10);
assert(avg3(1, 2, 2) == 1);
assert(avg3(-1, -2, -2) == -1);
assert(avg3(LLONG_MAX, LLONG_MAX, LLONG_MAX) == LLONG_MAX);
```

## Notes
- Use the source code from the attached file as the basis of your solution.
- You can add more of your tests to the main function, or you can change it freely. It is important to preserve conditional compilation.
- The assert macro is used in the example. If the parameter is a non-zero value, the macro does nothing. If the parameter is false (zero), the macro terminates the program and prints the line where the failure occurred. Therefore, if your implementation passes the example tests, the program will run and display nothing.
- At first glance, the problem appears trivial. This appearance is deceiving; the function must work correctly for all input values, such as the highest value LLONG_MAX in the example.
- The data type long long is 64 bits in size on the target platform. There is no larger data type available. Non-standard types __int128 and __float128 cannot be used (they are disabled).
- Boundary value testing is rated either 0% (the function returns incorrect results for some values) or 100% (everything works correctly).
- Update: available header files can be seen in the attached pattern. Other header files are not available and are not needed. Do not insert additional header files using #include, as the program will end with a compilation error.

