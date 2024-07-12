## D'Hondt Method

Following a series of global pandemics in Europe, the collapse of the international stock exchange, and an invasion by an alien race, the honest citizens of the New European Empire decided to introduce a new kind of election. In these elections, citizens vote for which party deserves a "reward". Several individuals from each party are chosen to work for a year in the uranium mines of Zážeh (formerly Zábřeh) as their reward. This positive motivation has helped to minimize corruption in this post-apocalyptic empire.

Your goal is to implement an application that uses the D’Hondt method to distribute places in the uranium mine among the various parties.

Input will include:

- N number of parties (an integer between 2 and 26), each party is represented for simplicity by a single character of the English alphabet (A - Z),
- On the following N lines, you receive a pair: character (party identifier) and the number of votes (a positive integer),
- The input concludes with the number of available positions.

Your task is to calculate the assignment of positions using the D’Hondt method for the individual parties and display the results. The D’Hondt method assigns individual places to parties progressively. In each step, it finds the party with the highest preference, and this party receives one place, while the preference for that party is decreased. The preference of a party is defined as the number of votes / (1 + number of seats held), if the party has not yet received a place, then the preference is number of votes / 1.42.

Example of the method in action:
```text
Party A Party B Party C
Votes 100 60 45
Place 1 70.42 42.25 31.69
Place 2 50 42.25 31.69
Place 3 33.33 42.25 31.69
```
The table shows the number of votes for individual parties and the party preference for each allocated place. The winning party for each round is highlighted in bold. As a result, Party A gains two places, Party B one place, and Party C none. The format of input and output can be seen in the example below. Parties are displayed in alphabetical order starting with Party A.

If the input is invalid, the program must detect this and display an error message. Display the error message on the standard output (not on the error output). Consider the input invalid if:

- The number of parties is less than 2 or more than 26,
- The party name is not a capital letter of the English alphabet (A-Z),
- The party name does not fall within the range from A to the number of parties (e.g., 5 => E),
- There is a duplicate party (e.g., Party A appears twice in the input),
- A party name or number of votes is missing,
- The number of votes is zero or negative,
- The number of places in the mines is not positive.

Sample program operation:

```text
Number of parties:
3
Parties and number of votes:
A 100
B 60
C 45
Number of miners:
3
Allocated counts:
A: 2
B: 1
C: 0

Number of parties:
5
Parties and number of votes:
C 24823
A 83647
D 20646
B 63181
E 9131
Number of miners:
8
Allocated counts:
A: 4
B: 3
C: 1
D: 0
E: 0
```

If there's a tie in preference points and a shortage of required positions, the program should handle these situations gracefully. An example from the sample run and provided test data shows a scenario where there is equality (2 parties, each with 10 votes, one position to fill). This input data is only in examples; such scenarios are excluded from the basic test on Progtest.

Notes:

- Sample runs capture the expected outputs of your program (in bold text) and the inputs provided by the user (in regular font). Bold highlighting is used here only to make the output more readable. Your program is expected to display text without highlighting (without HTML markup).
- A newline character (\n) is also present after the last line of output (even after any error message).
- Be mindful of the exact appearance of outputs. The output of your program is checked by a machine, which requires an exact match with the reference outputs. Any discrepancy, even a missing or additional space/newline, is considered an error. To quickly eliminate these issues, use the attached archive with a set of input and expected output data. Watch the video tutorial (Courses -> Video Tutorials) on how to use the test data and automate testing.
- Your program will be run in a restricted testing environment. It is limited by runtime (the limit is visible in the log of the reference solution) and also by the size of available memory (though this task should not have a problem with either limitation).
