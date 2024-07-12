# Calculator

The task is to create a program that processes simple mathematical expressions.

The input will consist of two decimal numbers separated by an operation sign and ending with an equals sign. Your task is to calculate the value based on the given operator:

- For `+` determine the sum,
- For `-` determine the difference,
- For `*` determine the product,
- For `/` determine the integer quotient (e.g., 3.5 / 1.5 = 2, how many times the divisor fits into the dividend).

The program will not handle other operations and will display an error message for them. The input and output format is

```text

Enter expression:
3.5 + 1.5 =
5

Enter expression:
3.5 / 1.5 =
2

Enter expression:
1000000 * 1.5e+8 =
1.5e+14

Enter expression:
7 / -1 =
-7

Enter expression:
abc / 1 =
Invalid input.

Enter expression:
4 & 10 =
Invalid input.

```


## Notes

The examples capture the expected outputs of your program (in bold) and the user inputs (in regular font). The bold formatting is used here for clarity in the assignment description only. Your program should display text without any formatting (no HTML markup).

The newline character (\n) is also present after the last line of output (including error messages).

Use double type for representing values. Do not use the float type as its precision may not be sufficient.

Be precise with the output format. The output of your program is checked by a machine that requires an exact match with the reference outputs. Any difference, including missing or extra spaces/newlines, is considered an error. To quickly eliminate these issues, use the attached archive with the set of input and expected output data. Watch the video tutorial (Courses -> Video Tutorials) on how to use test data and automate testing.

The resulting value is compared as a decimal number with a tolerance of 1 per mille.

Your program will run in a limited test environment. It is limited by runtime (the limit is visible in the reference solution log) and memory size (but this task should not have a problem with either).

The textual description of the structure of valid input data is not entirely exact. Therefore, we also attach a formal description of the input language in EBNF:

```text
input ::= { whiteSpace } decimal { whiteSpace } op { whiteSpace } decimal { whiteSpace } '='
whiteSpace ::= ' ' | '\t' | '\n' | '\r'
decimal ::= [ '+' | '-' ] integer [ '.' integer [ ( 'e' | 'E' ) [ '+' | '-' ] integer ] ] |
[ '+' | '-' ] '.' integer [ ( 'e' | 'E' ) [ '+' | '-' ] integer ]
integer ::= digit { digit }
digit ::= '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
op ::= '+' | '-' | '*' | '/'
```