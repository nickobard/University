## Phone Directory Access during a Pandemic

Due to the COVID-19 pandemic spiraling out of control once again, stricter measures are necessary. To improve contact tracing, the government legally requires direct access to the phone directories of traced citizens. Your task is to write a program that simplifies searching for contacts in these directories and generates the necessary reports.

Your task is to implement the function:

```cpp
bool report(const string& fileName, ostream& out);
```

- fileName is a text string containing the path to the phone directory and queries,
- out is the output stream where the report will be written,
- The return value of the function is false if there is an error during the processing of the file or the phone directory contained within, or true if the processing is successful without issues.

The input file first contains records of the phone directory. This is followed by a blank line and then a list of queries, to which your program must return responses on the provided output stream. Each record in the phone directory is separated by a new line, with the record containing the first name, last name, and telephone number. The items are separated by any number of white spaces (other than newline). Subsequent queries contain exactly one word.

The function searches for records that match either the full first name, last name, or both. Partial matches like "Joh" for "John" are not accepted. Suitable records should be printed to the specified stream, and the order on the output must correspond to the order in the phone directory. All outputs should be displayed on the passed output stream (not on standard cout nor error output cerr).

The format of the input and output can be seen below in the function's sample operation. If the input is invalid, the function must detect this and return false. Consider the input invalid if:

- an attribute is missing or extra,
- an attribute is missing or extra,
- the telephone number does not have exactly nine digits,
- the telephone number contains characters other than digits,
- the telephone number starts with 0,
- after the telephone number on the line, there is further input (white spaces may follow, but nothing else),
- a blank line is missing after the list of numbers.

Notes:

- In the attached archive, you will find sample runs of the program and test inputs.
- A newline character (\n) is also present after the last line of output (even after any potential error message).
- If you wish, you can use std::string, std::vector, std::array, and algorithms from the standard C++ library algorithm during implementation. Alternatively, you may use dynamically allocated arrays.
- To accomplish the task, using std::getline and/or std::stringstream may be useful.
- The task is focused on file handling, so you do not need to worry too much about time or memory demands.
- Update as of March 8, 2023: Do not use the std::ws manipulator, as due to the version of the compiler in the Progtest system, it may not function as expected. It should not be needed to solve the task.
