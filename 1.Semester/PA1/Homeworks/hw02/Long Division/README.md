## Long Division

The task is to implement a program that calculates the quotient and shows the intermediate steps, similar to long division.

The input to the program are two integers - the dividend and the divisor.

The output of the program is the quotient and the remainder. Additionally, the program displays the intermediate results (remainders at each step). The output is formatted so that the intermediate remainders are correctly aligned with the corresponding steps, see the example below. There is a newline after each line of output (including the last one).

The program must be able to detect incorrect input. If the input is invalid, the program will detect this, print an error message, and terminate. The format of the error message is shown in the example below. Note, there is a newline after any error message (`\n`). Send the error message to the standard output (printf), not to the error output. Consider it an error if:

- the value of the dividend or divisor is non-numeric,
- the dividend is negative,
- the divisor is zero or negative.

Sample program operation:
```plaintext
Enter two numbers:
546 37
 546 : 37 = 14
-37
 176
-148
  28 remainder
Enter two numbers:
1234 73
 1234 : 73 = 16
 -73
  504
 -438
   66 remainder
Enter two numbers:
123 4567
 123 : 4567 = 0
   0
 123 remainder
Enter two numbers:
1000 10
 1000 : 10 = 100
-10
   0
   0
    0
    0
    0 remainder
Enter two numbers:
9288492 6
 9288492 : 6 = 1548082
-6
 32
-30
```

Notes:
Sample runs capture the expected outputs of your program (bold text) and the inputs provided by the user (regular font). Bold highlighting is used here on the assignment page only to make the output more readable. Your program is only required to display the text without highlighting (without HTML markup).
The newline character (\n) is also present after the last line of output (even after any error message).
For storing values, the data type int is sufficient.