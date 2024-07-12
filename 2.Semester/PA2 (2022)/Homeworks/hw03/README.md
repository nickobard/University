## Date

The task is to implement a class that will represent a date. The represented dates must conform to the rules of the Gregorian calendar, and it is required that dates can be represented at least in the range from the year 2000 to 2030.

The CDate class must fulfill the following interface:

- **Constructor with parameters (y,m,d)**: Creates a new instance of the class with the date set according to the passed values. The constructor must check whether the given date is valid. If it is not valid, it must throw an `InvalidDateException`.
- **Operator +**: Allows an integer to be added to an instance of CDate, thus moving forward by the specified number of days (backward for a negative number).
- **Operator -**: Allows an integer to be subtracted from an instance of CDate, thus moving backward by the specified number of days (forward for a negative number).
- **Operator -**: Allows subtraction of two instances of CDate, returning the number of days between these two dates.
- **Operators ++ and --** (both prefix and postfix): Used to increment/decrement the date by one day. These operators behave in their usual manner.
- **Relational operators** (<, <=, >, >=, ==, !=): Enable comparison between two instances of CDate, where dates in the future are considered greater than those in the past.
- **Operator <<**: Allows an instance of CDate to be displayed in a stream. The display uses the ISO format (%Y-%m-%d, e.g., 2000-01-31). The default format used in the mandatory tests is this ISO format. Bonus tests require the implementation of the `date_format` manipulator, which allows control over the format.
- **Operator >>**: Allows an instance of CDate to be read from a given stream. In the mandatory tests, the date is expected in ISO format %Y-%m-%d. If the date cannot be read (due to format issues, invalid date, etc.), the operator ensures the fail bit is set and leaves the original content of the CDate instance unchanged. Like the output operator, the input can be controlled using the `date_format` manipulator, which is required in the bonus test.

**Submission Requirements:**
Submit a file containing the implemented CDate class and any additional supporting classes and functions. The class must meet the described public interface - if your submitted solution does not contain the described interface, a compilation error will occur. However, you may add additional methods (public or private) and member variables to the class. The submitted file must contain both the declaration of the class (interface description) and the definitions of methods, constructors, and destructor. It does not matter whether the methods are implemented inline or separately. The submitted file must not contain anything other than the implementation of the CDate class, especially not the insertion of header files and the `main` function (the function `main` and the insertion of header files may remain but only wrapped in conditional compilation directives as shown in the example below).

This task is not focused on speed. Given the range of tested values, it is feasible to use library calls for date conversions (ctime).

The task has both a mandatory and a bonus part. In the mandatory part, the `date_format` manipulator is not used, so only the default date format (%Y-%m-%d) is tested. In the bonus part, it is additionally required that this manipulator works correctly. If you decide to omit the bonus part, leave the provided "dummy" implementation of the manipulator in your source code (otherwise the code may not compile).

Bonus tests use your provided `date_format` manipulator, which describes the required conversions using a string. The format can include:

- Characters other than percentage characters - on input, such a character is expected at that position and is skipped. If the character is not found on input, it is considered an error. For output conversion, such a character is added to the output. In the ISO format %Y-%m-%d, such characters are the dashes.
- The percentage character followed by the day (%d), month (%m), or year (%Y), which occurs at that position in the date string. For input, a whole number specifying the day/month/year is expected; for output conversion, it means that the decimal value of the day/month/year, padded with zeros on the left, is added to the output.
- The percentage character followed by a character other than Y, m, or d (e.g., %x, %%, ...) indicates that such a character occurs/is to be displayed at that position in the date string (thus, in the example, x, %, ...). Thus, the ISO date format could equivalently be rewritten as %Y%-%m%-%d.

If the `date_format` manipulator is once sent into the stream, this format applies to all subsequent conversions until a further change of format (thus, it behaves similarly to manipulators like hex, ...). When implementing, keep in mind that a different manipulator may be set in each stream.

The output format can be arbitrary (an extreme example is the "hello kitty" format in the example). The input format has restrictions to ensure the input can be processed unambiguously: day, month, and year (%d, %m, and %Y) must be present in the format and exactly once. The example shows that input formats with missing or superfluous conversions lead to an error during subsequent loading.

**Notes:**
- The appendix contains the basis of implementation, runtime examples, and examples for the bonus test.
- Depending on the chosen implementation, the fact that some days do not have 24 hours may play a role.
- If you implement the manipulator, study the methods xalloc, register_callback, pword, and iword in the ios_base class.
- When solving the task, you will encounter the issue of leap years. A year is considered a leap year if it is divisible by 4 (e.g., 2020, 2024, ...). Years divisible by 100 are exceptions and are not leap years (e.g., the years 1900 and 2100 were/will not be leap years). However, years divisible by 400 are exceptions to this exception and are leap years (e.g., the year 2000 was a leap year). However, the task is simplified because only years from the limited range of 2000 - 2030 are given.
- When reading the day, month, and year from the stream, you should check that the number read has the correct number of digits (2 for day and month, 4 for year). In the basic tests, you do not need to check this (the generated values for days and months include any leading zeros). In the bonus test, you need to test more carefully; otherwise, loading in a general format may not work. The example run includes a test example for this.
- The solution to the task in the basic version is very short and straightforward. Such a solution cannot be used for code review. This time, only solutions that have passed all tests, including bonus tests, without errors can be submitted for code review.
