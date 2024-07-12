# Task 2: Shopping List

## Assignment

Your task is to implement three functions in the `shopping.php` script.

The first function `getPrice` takes a string as input (examples provided below) and returns a numeric value representing the item's price.

The second function `sortList` takes an array of strings (items) as input and returns it sorted in ascending order by price.

The third function `sumList` takes an array of strings (items) as input and returns a numeric value representing the total price.

## Project Structure

- `input` - directory containing sample input data
- `shopping.php` - script where you need to implement the functions mentioned above

## Execution

To execute and test, you can use examples from the `input` folder.

```shell
$ php shopping.php input/1.txt
```


## Description of Input

- Each line represents an item on the shopping list.
- The price is formatted as a decimal number. Thousands are separated by dots. The decimal part is optional.
- The currency is indicated as either `Kč` or `CZK`, or if the amount is a whole number without cents, it can be suffixed with `,-`.
- The currency indicator (`CZK` or `Kč` or `,-`) appears only after the amount.
- The placement of `CZK` can be before or after the amount, while `Kč` or `,-` only appear after the amount.
- There may or may not be a space separating the currency.

```text
Roll 5Kč
CZK400 Book
Beer 42,-
Bun 4 Kč
Butter 49,00 Kč
Gaming console 4,900 CZK
Radio CZK550
CZK 1,600.59 Natural 95
```