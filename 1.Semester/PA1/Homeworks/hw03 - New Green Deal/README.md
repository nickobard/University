## New Green Deal

The task is to implement a function (not the entire program, just the function) that calculates the electrical energy consumption in digital clocks.

The European Union rightly believes that it is necessary to save energy, no matter the cost. So far, this has applied to light bulbs, discharge lamps, and vacuum cleaners, but it is expected that this progressive trend will also affect other energy-intensive devices. To assist the hard work of EU officials, we provide them with an analytical tool in this task, which can be used to examine the energy intensity of digital clocks with a mechanical seven-segment display over the long term.

The clock displays time on a seven-segment display. Time is displayed in a 24-hour format, from 00 00 00 to 23 59 59. The display is mechanical, each digit is made up of 7 segments, each segment being either a light or dark rectangle. If there is no change to a given segment, no energy is needed. Conversely, changing a dark segment to light or vice versa costs energy, for simplicity, we assume 1J per segment change. The digits on the seven-segment display have a standard shape, described as:
```text
 -         -    -         -    -    -    -    -                                                                     
| |    |    |    |  | |  |    |      |  | |  | |                                                                       
           -    -    -    -    -         -    -                                                                     
| |    |  |      |    |    |  | |    |  | |    |                                                                       
 -         -    -         -    -         -    -
```
                                                                     
Our function will receive two time data points - start and end of the time interval. Both start and end are given by the year, month, day, hour, and minute. The function calculates how much energy the clock consumes during this time.

The required function interface:

```c
int energyConsumption ( int y1, int m1, int d1, int h1, int i1,
                        int y2, int m2, int d2, int h2, int i2, 
                        long long int * consumption )
```

- y1, m1, d1, h1, i1 are input parameters representing the year, month, day, hour, and minute at the start of the interval,
- y2, m2, d2, h2, i2 are input parameters representing the year, month, day, hour, and minute at the end of the interval,
- consumption is the output parameter into which the function stores the calculated consumption in the specified period. Consumption is returned in joules (J). The parameter will be set by the function only if the input parameters are correct. If incorrect inputs are given, the value cannot be determined. In such cases, the function signals failure and leaves this output parameter unchanged. The calculated value includes consumption for all changes to the display content made between the first and last displayed time data. For example:

```c
assert ( energyConsumption ( 2400, 2, 29, 12, 0,
2400, 2, 29, 12, 1, &consumption ) == 1
&& consumption == 204LL );
```

During this time, 60 changes of displayed seconds (200J) and change of minutes from 00 to 01 (4J) occurred.

Return value of the function will be set to 1 for success (correct input parameters) or 0 for failure (incorrect input parameters).

If incorrect input parameters are given, a return value of 0 (failure) is necessary. Correct input values must meet:

- Year is greater than or equal to 1600,
- Month is valid (1 to 12),
- Day is valid (1 to the number of days in the month),
- Hour is valid (0 to 23),
- Minute is valid (0 to 59),
- The specified moment at the start of the interval does not occur after the specified moment at the end of the interval.

Submit the source file containing the implementation of the required function energyConsumption. Add your other supporting functions called from energyConsumption to the source file. The function will be called from the testing environment, so it is important to precisely follow the specified interface of the function. Use the code from the example below as a basis for implementation. The code lacks filling in the function energyConsumption (and any other supporting functions). The example includes a test function main, the values provided are used in the basic test. Note that the inclusion of header files and the function main are wrapped in a conditional compilation block (#ifdef/#endif). Please retain the blocks of conditional compilation in the submitted source file. Conditional compilation will simplify your work. When compiling on your computer, you can normally run and test the program. When compiling on Progtest, the function main and the inclusion of header files "disappear," thus will not collide with the header files and the main function of the testing environment.


When calculating time, we consider the Gregorian calendar. Thus, months always have 30 or 31 days, except for February, which has 28 days (non-leap year) or 29 days (leap year). According to the Gregorian calendar:

- Years are not leap years,
- except for years divisible by 4, which are leap years,
- except for years divisible by 100, which are not leap years,
- except for years divisible by 400, which are leap years,
- except for years divisible by 4000, which are not leap years.
 

Thus, years 1901, 1902, 1903, 1905, ... are non-leap years (rule 1), years 1904, 1908, ..., 1996, 2004, ... are leap years (rule 2), years 1700, 1800, 1900, 2100, ... are not leap years (rule 3), years 1600, 2000, 2400, ..., 3600, 4400, ... are leap years (rule 4) and years 4000, 8000, ... are not leap years (rule 5).

Your program will be run in a restricted testing environment. It is limited by runtime (the limit is visible in the log of the reference solution) and also by the size of the available memory. Time limits are set so that a reasonable implementation of a naive algorithm passes all mandatory tests. Solutions functioning in mandatory tests can score a nominal 100% points. A bonus test requires time-efficient calculation even for large intervals (high years significantly exceeding 4000).

### Hint:

Copy the attached file and use it as the basis for your solution.
You can add more of your tests to the function main, or you can change it freely. It is important to maintain conditional compilation. Note, using foreign tests is considered copying.
Working with five values (year, month, day, hour, minute) is difficult (for example, when comparing). It is better to convert these values to some other representation, ideally into a single number.
You must do many calculations twice - for the start and end of the interval. It's a good idea to create helper functions, which you call twice.
In mandatory tests, the years provided do not exceed the year 4000.
For large intervals (bonus test), the total consumption is enormous. The range of the data type int is insufficient. Therefore, the function has a parameter long long int, which is sufficient.
The example uses the assert macro. If the parameter is a non-zero value, the macro does nothing. If the parameter is false (zero), the macro terminates the program and prints the line where the failure occurred. If your implementation passes the example tests, the program will run and display nothing.
A naive solution might try to generate all time data within the specified range and count the number of changed segments. Such an approach will be very slow and very likely will not pass the time limit. Try to make your solution more efficient by skipping longer time intervals, for which you precalculate their consumption. A suitable granularity might be, for example, an entire day, as the consumption for one whole day will always be the same.