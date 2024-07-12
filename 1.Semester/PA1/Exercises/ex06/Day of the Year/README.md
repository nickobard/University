# Day of the Year

The task is to implement a function (not a whole program, just a function) that determines which day of the year a given date is.

The function has the following interface:

```c
int dateToIndex(int day, int month, int year, int * idx);
```

- The input parameters of the function are day, month, and year, which are to be verified.
- idx is the output parameter indicating the ordinal number of the given day from the beginning of the year. For January 1st, the return value is 1. If the function succeeds, it writes the ordinal number of the day into its output parameter idx. If the function fails (invalid parameter values), it leaves the output parameter unchanged.
- The return value of the function signals success (value 1) and in the case of invalid parameters signals failure (value 0).


Errors are considered:

- year is less than 2000 (all dates before 2000 are considered invalid),
- month is out of the range 1 to 12,
- day is invalid (out of 1 to the number of days in the month).

Example usage of the function:

```c

assert(dateToIndex( 1,  1, 2000, &days) == 1 && days == 1);
assert(dateToIndex( 1,  2, 2000, &days) == 1 && days == 32);
assert(dateToIndex(29,  2, 2000, &days) == 1 && days == 60);
assert(dateToIndex(29,  2, 2001, &days) == 0);
assert(dateToIndex( 1, 12, 2000, &days) == 1 && days == 336);
assert(dateToIndex(31, 12, 2000, &days) == 1 && days == 366);
assert(dateToIndex( 1,  1, 1999, &days) == 0);
assert(dateToIndex( 6,  7, 3600, &days) == 1 && days == 188);
assert(dateToIndex(29,  2, 3600, &days) == 1 && days == 60);
assert(dateToIndex(29,  2, 4000, &days) == 0);

```

## Notes:

When calculating time, we consider the Gregorian calendar. Thus, months always have 30 or 31 days, with the exception of February, which has 28 days (non-leap year) or 29 days (leap year). According to the Gregorian calendar:

- Years are not leap years,
- except for years divisible by 4, which are leap years,
- except for years divisible by 100, which are not leap years,
- except for years divisible by 400, which are leap years,
- except for years divisible by 4000, which are not leap years.

Thus, the years 2001, 2002, 2003, 2005, … are not leap years (rule 1), the years 2004, 2008, …, 2096, 2104, … are leap years (rule 2), the years 2100, 2200, 2300, … are not leap years (rule 3), the years 2000, 2400, …, 3600, 4400, … are leap years (rule 4) and the years 4000, 8000, … are not leap years (rule 5).


Use the source code from the attached file as the basis for your solution. You can also add your own tests to the main function or modify it as you like. It is important to maintain conditional compilation.


The example uses the assert macro. If the parameter is a non-zero value, the macro does nothing. If the parameter is false (zero), the macro terminates the program and prints the line where the failure occurred. Therefore, if your implementation passes the sample tests, the program will run and display nothing.



Update: The available header files can be seen in the attached template. Other header files are not available and are not needed. Do not include additional header files using #include, the program will fail to compile.
