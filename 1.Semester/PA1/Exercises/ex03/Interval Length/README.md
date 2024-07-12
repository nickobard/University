# Task: Calculate Time Interval Length

The task is to create a program that calculates the length of a time interval.

The input will be the start time of the interval `t1` and the end time of the interval `t2`. The time is always given in the format `h:m:s,ms` (hour, minute, second, fraction of a second). The program will calculate the length of this time interval and display it in the format `h:m:s,ms`. The expected behavior is shown in the examples below.

If the input is invalid, the program must detect it and display an error message. Display error messages to standard output (not standard error). Consider the following as errors:

- Non-numeric values,
- Values out of bounds (max. 23h, max. 59 min, max. 59 sec, max. 999 ms),
- Missing comma or colon,
- The start time is greater than the end time.

## Program Run Examples

```text
Enter time t1:
11:45:20,456
Enter time t2:
12:07:54,349
Duration: 0:22:33,893

Enter time t1:
15:18:34,232
Enter time t2:
15:18:34,293
Duration: 0:00:00,061

Enter time t1:
12:00:00,000
Enter time t2:
12:00:00,000
Duration: 0:00:00,000

Enter time t1:
01:01:01,001
Enter time t2:
07:07:07,007
Duration: 6:06:06,006

Enter time t1:
1:1:1,001
Enter time t2:
7:7:7,007
Duration: 6:06:06,006

Enter time t1:
1:1:1,001
Enter time t2:
17:7:7,007
Duration: 16:06:06,006

Enter time t1:
12:30:00,000
Enter time t2:
12:00:00,000
Invalid input.

Enter time t1:
15:30:34,123
Enter time t2:
15:60:34,123
Invalid input.

Enter time t1:
15:40:21.745
Invalid input.

```

## Notes

The examples capture the expected outputs of your program (in bold) and the user inputs (in regular font). The bold formatting is used here for clarity in the assignment description only. Your program should display text without any formatting (no HTML markup).

The newline character is also present after the last line of output (including error messages).

To read the input, the `scanf` function is suitable. The `scanf` function can also easily check for the presence of colons and commas.

Do not use floating-point numbers for input (the input deliberately uses a comma, not a dot). Also, processing the input as a string is unnecessarily laborious.

Be precise with the output format. The output of your program is checked by a machine that requires an exact match with the reference outputs. Any difference, including missing or extra spaces/newlines, is considered an error. To quickly eliminate these issues, use the attached archive with the set of input and expected output data. Watch the video tutorial (Courses -> Video Tutorials) on how to use test data and automate testing.

Display hours with 2 places without leading zeros, minutes and seconds with 2 places with leading zeros, and milliseconds with 3 places with leading zeros.

You can rely on the input having milliseconds specified with 3 digits. The exception is the last (bonus) test, where the number of milliseconds can be specified with 1, 2, or 3 digits (e.g., `1:2:3,4` means 400 ms). This input is more difficult to process, but it can be handled using the `scanf` function.

Your program will run in a limited test environment. It is limited by runtime (the limit is visible in the reference solution log) and memory size (but this task should not have a problem with either). The test environment also prohibits using some "dangerous functions" - functions for running programs, working with the network, etc. If these functions are used, the program will not run. If your program uses the following call:

```c
int main ( void )
{
    ...
    system ( "pause" ); /* to prevent the program window from closing */
    return 0;
}
```

This will not work in the test environment - running another program is prohibited. (Even if the program runs, it will be rejected because there will be no one to "press" the pause, and the program will wait indefinitely, exceeding the maximum runtime.) If you want to keep the pause for testing on your computer and ensure the program runs correctly, use the following trick:

```c

int main ( void )
{
    ...
    #ifndef __PROGTEST__
    system ( "pause" ); /* this is invisible to Progtest */
    #endif /* __PROGTEST__ */
    return 0;
}

```