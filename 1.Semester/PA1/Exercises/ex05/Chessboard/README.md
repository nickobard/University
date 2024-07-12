# Task: Display a Chessboard

The task is to create a program that displays a chessboard on the screen.

The input to the program consists of two integers - the size of the chessboard (number of squares in width and height) and the size of a square (number of characters in width and height of one square).

The output of the program is the displayed chessboard. The chessboard will be composed of space characters (white squares) and the character X (black squares). The entire chessboard will be framed. In the upper-left corner, there will always be a white square. The chessboard is square (the number of squares is the same in both directions), and the squares are also square (the number of characters per square is the same in both directions).

If the input is invalid, the program must detect it and display an error message. Display error messages to standard output (not standard error). Consider the following as errors:

- The input does not consist of two valid integers,
- The numbers in the input are negative or zero.

## Program Run Examples

```text

Enter the number of squares:
5
Enter the size of the square:
3
+---------------+
|   XXX   XXX   | 
|   XXX   XXX   | 
|   XXX   XXX   | 
|XXX   XXX   XXX|
|XXX   XXX   XXX|
|XXX   XXX   XXX|
|   XXX   XXX   |
|   XXX   XXX   |
|   XXX   XXX   |
|XXX   XXX   XXX|
|XXX   XXX   XXX|
|XXX   XXX   XXX|
|   XXX   XXX   |
|   XXX   XXX   |
|   XXX   XXX   |
+---------------+

Enter the number of squares:
8
Enter the size of the square:
4
+--------------------------------+
|    XXXX    XXXX    XXXX    XXXX|
|    XXXX    XXXX    XXXX    XXXX|
|    XXXX    XXXX    XXXX    XXXX|
|    XXXX    XXXX    XXXX    XXXX|
|XXXX    XXXX    XXXX    XXXX    |
|XXXX    XXXX    XXXX    XXXX    |
|XXXX    XXXX    XXXX    XXXX    |
|XXXX    XXXX    XXXX    XXXX    |
|    XXXX    XXXX    XXXX    XXXX|
|    XXXX    XXXX    XXXX    XXXX|
|    XXXX    XXXX    XXXX    XXXX|
|    XXXX    XXXX    XXXX    XXXX|
|XXXX    XXXX    XXXX    XXXX    |
|XXXX    XXXX    XXXX    XXXX    |
|XXXX    XXXX    XXXX    XXXX    |
|XXXX    XXXX    XXXX    XXXX    |
|    XXXX    XXXX    XXXX    XXXX|
|    XXXX    XXXX    XXXX    XXXX|
|    XXXX    XXXX    XXXX    XXXX|
|    XXXX    XXXX    XXXX    XXXX|
|XXXX    XXXX    XXXX    XXXX    |
|XXXX    XXXX    XXXX    XXXX    |
|XXXX    XXXX    XXXX    XXXX    |
|XXXX    XXXX    XXXX    XXXX    |
|    XXXX    XXXX    XXXX    XXXX|
|    XXXX    XXXX    XXXX    XXXX|
|    XXXX    XXXX    XXXX    XXXX|
|    XXXX    XXXX    XXXX    XXXX|
|XXXX    XXXX    XXXX    XXXX    |
|XXXX    XXXX    XXXX    XXXX    |
|XXXX    XXXX    XXXX    XXXX    |
|XXXX    XXXX    XXXX    XXXX    |
+--------------------------------+

Enter the number of squares:
2
Enter the size of the square:
0
Invalid input.


Enter the number of squares:
asdf
Invalid input.

```


## Notes

The examples capture the expected outputs of your program (in bold) and the user inputs (in regular font). The bold formatting is used here for clarity in the assignment description only. Your program should display text without any formatting (no HTML markup).

The newline character (\n) is also present after the last line of output (including error messages).

Be precise with the output format. The output of your program is checked by a machine that requires an exact match with the reference outputs. Any difference, including missing or extra spaces/newlines, is considered an error. To quickly eliminate these issues, use the attached archive with the set of input and expected output data. Watch the video tutorial (Courses -> Video Tutorials) on how to use test data and automate testing.

The output of the program can be very wide/long, so it is worth redirecting the output to a file and viewing it in an editor.
