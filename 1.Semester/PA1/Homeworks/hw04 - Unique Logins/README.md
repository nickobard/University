## Unique Visits

The task is to create a program that processes logs and counts unique visits.

We assume that individual accesses to a WWW server are recorded. Users who access are each marked with a unique identifier. The identifier is an integer in the closed interval from 0 to 99999. Individual accesses are given in the form of the command + id, for example:
```text
+ 123
+ 456
+ 123
+ 123
+ 789
```

Here, positions 0, 2, and 3 are accesses by user 123, position 1 is an access by user 456, and position 4 is an access by user 789.
From the recorded accesses, information about the number of unique users needs to be calculated. For the calculation, a range will be specified that is to be analyzed. The format is ? from to, where from and to are positions from which to count unique users. For example, for the sample, a query in the form ? 0 4 would give the response 3 / 5 - 3 unique users out of a total of 5 records in the queried range.

The program's input consists of accesses and queries, which can be arbitrarily mixed. The program processes the input, saves information about accesses, and continuously handles queries. Input processing ends either by detecting an error (incorrect input) or by reaching the end of the input (EOF). There are at most 1,000,000 accesses in total on the input, and the number of requests for calculating unique accesses is not upper limited.

The output of the program is a reaction to each input:

- For each access, the program displays which visit it is for that user,
- For a query on the number of unique accesses, the program displays information about the number of unique users in the specified range / total number of accesses in the defined range.

If the input is invalid, the program must detect this and display an error message. Display the error message on the standard output (not on the error output). Consider it an error when adding access if:

- user id is missing,
- id is not an integer,
- id is not in the interval < 0 ; 99999 >, or
- there are more than 1,000,000 accesses.

Consider it an error in the query if:

- information from and to is missing,
- from / to are not integers,
- from is less than 0,
- to is greater than or equal to the number of accesses registered so far, or
- from is greater than to.

It is also an error if the input contains neither an access addition nor a query.

Sample operation of the program:

```text
Requirements:
+ 10
> first visit
+ 20
> first visit
+ 99999
> first visit
+ 5
> first visit
+ 20
> visit #2
+ 25
> first visit
+ 10
> visit #2
? 0 6
> 5 / 7
? 0 5
> 5 / 6
? 1 6
> 5 / 6
? 1 5
> 4 / 5
? 2 6
> 5 / 5
? 2 5
> 4 / 4
? 2 4
> 3 / 3
? 2 3
> 2 / 2
? 2 2
> 1 / 1
+ 5
> visit #2
+ 10
> visit #3
+ 5
> visit #3
+ 20
> visit #3
? 0 10
> 5 / 11
? 7 10
> 3 / 4
? 1 11
Incorrect input.
Requirements:
+ 10
> first visit
+ 20
> first visit
+ 30
> first visit
? 2 1
Incorrect input.
Requirements:
+ 12
> first visit
* 33
Incorrect input.
```
Notes:
Sample runs capture the expected outputs of your program (bold text) and the inputs provided by the user (regular font). Bold highlighting is used here on the assignment page only to make the output more readable. Your program is only required to display text without highlighting (without HTML markup).
The newline character (\n) is also present after the last line of output (even after any error message).
Take advantage of the fact that the number of different visitor identifiers is limited (0 to 99999) and the number of accesses is also capped (1,000,000). If you need to store, for example, all input accesses in memory, a statically allocated array will suffice.
The submitted program is tested with multiple tests of increasing difficulty. First, the correctness of the solution is checked, then the correct operation with the array (memory debugger test), and finally the efficiency of the solution.
The basic solution does not have to be efficient; a naive (quadratic) algorithm for searching for unique values is sufficient. Such a solution will pass the mandatory tests and some optional tests. It will be rated with a maximum of 100% points.
The first bonus test checks the efficiency of the submitted program. Long inputs and queries over long intervals are given. A naive algorithm is not sufficiently efficient and fails to compute within the set time limit.
The second bonus test further checks the efficiency of the used algorithm. Long inputs are given, queries process large intervals of accesses and queries, and many are given. To manage the time limit, the recorded accesses need to be pre-processed so that the program does not have to repeatedly calculate what only needs to be calculated once.
A program that passes all mandatory and optional tests at 100% can be used for a code review. (For code review, it is not necessary to pass bonus tests).
