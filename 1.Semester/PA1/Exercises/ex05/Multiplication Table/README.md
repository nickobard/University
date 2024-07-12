# Multiplication Table

The task is to create a program that displays a multiplication table.

The input to the program is an integer - the limit `n`.

The output of the program is a multiplication table ranging from 1x1 to `n x n`. The table is displayed without duplicate values, in a triangular form. All columns have the same width, which is determined by the number of digits in the largest product in the table, increased by 1. After the last number on a line, a newline character follows, meaning there are no extra white characters at the ends of the lines.

If the input is invalid, the program must detect it and display an error message. Display error messages to standard output (not standard error). Consider the following as errors:

- The input is not a valid integer,
- The number in the input is negative or zero.

## Program Run Examples

```text

Range:
10
| 10 9 8 7 6 5 4 3 2 1
---+----------------------------------------
1| 10 9 8 7 6 5 4 3 2 1
2| 20 18 16 14 12 10 8 6 4
3| 30 27 24 21 18 15 12 9
4| 40 36 32 28 24 20 16
5| 50 45 40 35 30 25
6| 60 54 48 42 36
7| 70 63 56 49
8| 80 72 64
9| 90 81
10| 100



Range:
8
| 8 7 6 5 4 3 2 1
--+------------------------
1| 8 7 6 5 4 3 2 1
2| 16 14 12 10 8 6 4
3| 24 21 18 15 12 9
4| 32 28 24 20 16
5| 40 35 30 25
6| 48 42 36
7| 56 49
8| 64



Range:
32
| 32 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
----+----------------------------------------------------------------------------------------------------------------------------------------------------------------
1| 32 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
2| 64 62 60 58 56 54 52 50 48 46 44 42 40 38 36 34 32 30 28 26 24 22 20 18 16 14 12 10 8 6 4
3| 96 93 90 87 84 81 78 75 72 69 66 63 60 57 54 51 48 45 42 39 36 33 30 27 24 21 18 15 12 9
4| 128 124 120 116 112 108 104 100 96 92 88 84 80 76 72 68 64 60 56 52 48 44 40 36 32 28 24 20 16
5| 160 155 150 145 140 135 130 125 120 115 110 105 100 95 90 85 80 75 70 65 60 55 50 45 40 35 30 25
6| 192 186 180 174 168 162 156 150 144 138 132 126 120 114 108 102 96 90 84 78 72 66 60 54 48 42 36
7| 224 217 210 203 196 189 182 175 168 161 154 147 140 133 126 119 112 105 98 91 84 77 70 63 56 49
8| 256 248 240 232 224 216 208 200 192 184 176 168 160 152 144 136 128 120 112 104 96 88 80 72 64
9| 288 279 270 261 252 243 234 225 216 207 198 189 180 171 162 153 144 135 126 117 108 99 90 81
10| 320 310 300 290 280 270 260 250 240 230 220 210 200 190 180 170 160 150 140 130 120 110 100
11| 352 341 330 319 308 297 286 275 264 253 242 231 220 209 198 187 176 165 154 143 132 121
12| 384 372 360 348 336 324 312 300 288 276 264 252 240 228 216 204 192 180 168 156 144
13| 416 403 390 377 364 351 338 325 312 299 286 273 260 247 234 221 208 195 182 169
14| 448 434 420 406 392 378 364 350 336 322 308 294 280 266 252 238 224 210 196
15| 480 465 450 435 420 405 390 375 360 345 330 315 300 285 270 255 240 225
16| 512 496 480 464 448 432 416 400 384 368 352 336 320 304 288 272 256
17| 544 527 510 493 476 459 442 425 408 391 374 357 340 323 306 289
18| 576 558 540 522 504 486 468 450 432


Range:
asdf
Invalid input.

```


## Notes:

The examples capture the expected outputs of your program (in bold) and the user inputs (in regular font). The bold formatting is used here for clarity in the assignment description only. Your program should display text without any formatting (no HTML markup).

The newline character (\n) is also present after the last line of output (including error messages).

Be precise with the output format. The output of your program is checked by a machine that requires an exact match with the reference outputs. Any difference, including missing or extra spaces/newlines, is considered an error. To quickly eliminate these issues, use the attached archive with the set of input and expected output data. Watch the video tutorial (Courses -> Video Tutorials) on how to use test data and automate testing.

The output of the program can be very wide/long, so it is worth redirecting the output to a file and viewing it in an editor.

**HINT:** In this example, the output conversion `%*d` is useful.