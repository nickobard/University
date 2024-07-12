## Quotes

The task is to create a program that displays selected quotes.

The input of the program is a single whole number. This number ranges from 1 to 5 and determines which quote should be displayed.

The output of the program is the quote corresponding to the given number in the input. The quotes corresponding to each number are shown in the sample program runs below. Note that there is a newline character (`\n`) after the quote text.

If the input is invalid, the program must detect this and display an error message. Display the error message on the standard output (not on the error output). Consider it an error if:

- it is not possible to read a whole number from the input,
- the number read from the input is outside the interval 1 to 5.

When programming, pay attention to the exact form of the outputs. The output of your program is checked by a machine that requires an exact match with the reference outputs. Any discrepancy, even a missing or extra space/newline, is considered an error. To quickly eliminate these problems, use the attached archive with a set of input and expected output data. Look at the video tutorial (courses -> educational videos) on how to use the test data and how to automate testing.

Your program will be run in a restricted testing environment. It is limited by runtime (the limit is visible in the log of the reference solution) and also by the amount of available memory (but this task should not have a problem with either limitation). The testing environment also prohibits the use of some "dangerous functions" -- functions for running a program, working with the network, etc. If these functions are used, the program will not start. You may use the following call in your program:

```c
int main ( int argc, char * argv [] )
{
 
  ...
     
  system ( "pause" ); /* so the program window does not close */
  return 0;
}
```

This will not work in the testing environment - running another program is prohibited. (Even if the program started, it would be rejected. There would be no one to "unpause" it, the program would wait indefinitely and thus exceed the maximum runtime.) So, if you want to keep the pause for testing on your computer and at the same time ensure that the program will run correctly, use the following trick:
```c
int main ( int argc, char * argv [] )
{
 
  ...

#ifndef __PROGTEST__
  system ( "pause" ); /* this is not seen by progtest */
#endif /* __PROGTEST__ */
  return 0;
}
```

Sample program operation:


```text
ml' nob:
1
Qapla'
noH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.
ml' nob:
2
Qapla'
Qu' buSHa'chugh SuvwI', batlhHa' vangchugh, qoj matlhHa'chugh, pagh ghaH SuvwI''e'.
ml' nob:
3
Qapla'
qaStaHvIS wa' ram loS SaD Hugh SIjlaH qetbogh loD.
ml' nob:
4
Qapla'
Ha'DIbaH DaSop 'e' DaHechbe'chugh yIHoHQo'.
ml' nob:
5
Qapla'
leghlaHchu'be'chugh mIn lo'laHbe' taj jej.
ml' nob:
0
luj
ml' nob:
6
luj
ml' nob:
abc
luj

```

Notes:
The newline character (\n) is also after the last line of output (even after any error message).
The program prompts and quotes are deliberately chosen to be difficult to manually transcribe. This task also aims to teach you efficient use of the computer, including copy & paste functions (which unfortunately some students do not know or cannot use). Try and learn to use copy & paste both under Windows and UNIX (Linux), it will be handy for the final test!
Manual checking of the consistency between your output and the reference output is tedious, and people often overlook a small difference when comparing. Especially it applies to the text in the task, which is not understandable to most people. This is again intentional. Use the free time at the beginning of the semester to learn to efficiently test your programs. Look at the mentioned video tutorial (courses -> educational videos) and use your computer for comparison. In subsequent tasks, this will save you a lot of time.
Consider inputs like 1.23 or 1abcd as correct. Basic usage of the scanf function will interpret such inputs as a number (here number 1) and will not read the rest of the input. It is possible, of course, to extend the program to reject such inputs, but it is not necessary to do so in this task. Automated testing does not specify inputs of this type.