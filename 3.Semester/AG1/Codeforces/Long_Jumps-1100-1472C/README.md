# [C. Long Jumps](https://codeforces.com/contest/1472/problem/C)


```text
time limit per test: 2 seconds
memory limit per test: 256 megabytes
input: standard input
output: standard output
```

Polycarp found under the Christmas tree an array 𝑎
 of 𝑛
 elements and instructions for playing with it:

- At first, choose index 𝑖
 (1≤𝑖≤𝑛
) — starting position in the array. Put the chip at the index 𝑖
 (on the value 𝑎𝑖
).
- While 𝑖≤𝑛
, add 𝑎𝑖
 to your score and move the chip 𝑎𝑖
 positions to the right (i.e. replace 𝑖
 with 𝑖+𝑎𝑖
).
- If 𝑖>𝑛
, then Polycarp ends the game.


For example, if 𝑛=5
 and 𝑎=[7,3,1,2,3]
, then the following game options are possible:

- Polycarp chooses 𝑖=1
. Game process: 𝑖=1⟶+78
. The score of the game is: 𝑎1=7
.
- Polycarp chooses 𝑖=2
. Game process: 𝑖=2⟶+35⟶+38
. The score of the game is: 𝑎2+𝑎5=6
.
- Polycarp chooses 𝑖=3
. Game process: 𝑖=3⟶+14⟶+26
. The score of the game is: 𝑎3+𝑎4=3
.
- Polycarp chooses 𝑖=4
. Game process: 𝑖=4⟶+26
. The score of the game is: 𝑎4=2
.
- Polycarp chooses 𝑖=5
. Game process: 𝑖=5⟶+38
. The score of the game is: 𝑎5=3
.
Help Polycarp to find out the maximum score he can get if he chooses the starting index in an optimal way.

### Input
The first line contains one integer 𝑡
 (1≤𝑡≤104
) — the number of test cases. Then 𝑡
 test cases follow.

The first line of each test case contains one integer 𝑛
 (1≤𝑛≤2⋅105
) — the length of the array 𝑎
.

The next line contains 𝑛
 integers 𝑎1,𝑎2,…,𝑎𝑛
 (1≤𝑎𝑖≤109
) — elements of the array 𝑎
.

It is guaranteed that the sum of 𝑛
 over all test cases does not exceed 2⋅105
.

### Output
For each test case, output on a separate line one number — the maximum score that Polycarp can get by playing the game on the corresponding array according to the instruction from the statement. Note that Polycarp chooses any starting position from 1
 to 𝑛
 in such a way as to maximize his result.

### Example
```text
input
4
5
7 3 1 2 3
3
2 1 4
6
2 1000 2 3 995 1
5
1 1 1 1 1

output
7
6
1000
5

```

### Note
The first test case is explained in the statement.

In the second test case, the maximum score can be achieved by choosing 𝑖=1
.

In the third test case, the maximum score can be achieved by choosing 𝑖=2
.

In the fourth test case, the maximum score can be achieved by choosing 𝑖=1
.