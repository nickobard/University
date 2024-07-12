# Equation

The task is to create a program that checks simple mathematical equations.

The input will be a simple equation in the form `a @ b = c`, where `a`, `b`, and `c` are decimal numbers, and the `@` character defines an arithmetic operation. Your task is to determine whether the equation is valid. Supported operations are:

- `+` for addition,
- `-` for subtraction,
- `*` for multiplication,
- `/` for integer division (e.g., 3.5 / 1.5 = 2, how many times the divisor fits into the dividend).

If the equation is correct, output "Rovnice je spravne." If the equation is incorrect, output the left and right values separated by the sequence `!=`. The input and output format is shown in the examples of the program's operation below.

If the input is invalid, the program must detect it and display an error message. Display error messages to standard output (not standard error). Consider the following as errors:

- The input number is not a valid decimal number,
- The divisor is 0 for the `/` operation,
- The numbers are not separated by a valid operator (`+`, `-`, `*`, or `/`),
- The equation does not contain the `=` character.

## Program Run Examples

```text

Enter equation:
3.5 + 1.5 = 5
Rovnice je spravne.

Enter equation:
3.5 / 1.5 = 2
Rovnice je spravne.

Enter equation:
8 / -1 = -8
Rovnice je spravne.

Enter equation:
1.44 + 12.25 = 13.69
Rovnice je spravne.

Enter equation:
1.44 + 2.55 = 4
3.99 != 4

Enter equation:
abc / 1 = 2
Nespravny vstup.

Enter equation:
4 & 10 = 1
Nespravny vstup.

```


## Notes

The examples capture the expected outputs of your program (in bold) and the user inputs (in regular font). The bold formatting is used here for clarity in the assignment description only. Your program should display text without any formatting (no HTML markup).

The newline character (\n) is also present after the last line of output (including error messages).

Use double type for representing values. Do not use the float type as its precision may not be sufficient.

Be precise with the output format. The output of your program is checked by a machine that requires an exact match with the reference outputs. Any difference, including missing or extra spaces/newlines, is considered an error. To quickly eliminate these issues, use the attached archive with the set of input and expected output data. Watch the video tutorial (Courses -> Video Tutorials) on how to use test data and automate testing.

Comparison must respect the precision achievable with the double data type. Given the simple calculations, consider about 12-14 significant digits of the result.

Your program will run in a limited test environment. It is limited by runtime (the limit is visible in the reference solution log) and memory size (but this task should not have a problem with either).

The textual description of the structure of valid input data is not entirely exact. Therefore, we also attach a formal description of the input language in EBNF:

```text
input ::= { whiteSpace } formula { whiteSpace } '=' { whiteSpace } decimal { whiteSpace }
formula ::= decimal { whiteSpace } op { whiteSpace } decimal
whiteSpace ::= ' ' | '\t' | '\n' | '\r'
decimal ::= [ '+' | '-' ] integer [ '.' integer [ ( 'e' | 'E' ) [ '+' | '-' ] integer ] ] |
[ '+' | '-' ] '.' integer [ ( 'e' | 'E' ) [ '+' | '-' ] integer ]
integer ::= digit { digit }
digit ::= '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
op ::= '+' | '-' | '*' | '/'
```