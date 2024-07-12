# Task 3 - Classes

## 1. Class Bag

Implement the `Bag` class located in `classes/Bag.php`. The class has 7 methods:

- `add($item)` - adds an item to the collection, does not return anything
- `clear()` - empties the collection
- `contains($item)` - returns `true` if the item is in the collection, `false` otherwise
- `elementSize($item)` - returns the count of occurrences of the given item
- `isEmpty()` - returns `true` if the collection is empty, `false` otherwise
- `remove()` - removes an item from the collection; if the item is not present, nothing happens; if there are multiple occurrences, only one is removed
- `size()` - returns the total number of items in the collection


## 2. Autoloader

In the `main.php` file, there is an example of usage (you can use it to better understand the task). Implement and register an autoloader that ensures classes from the `classes` directory are loaded.


## 3. Class Set

Create a new class `Set` as a subclass of `Bag` that behaves as follows:

- `add($item)` - adds an item to the collection; if the item is already there, nothing happens
- `clear()` - empties the collection
- `contains($item)` - returns `true` if the item is in the collection, `false` otherwise
- `elementSize($item)` - returns the count of occurrences of the given item; in a `Set`, this is 0 or 1
- `isEmpty()` - returns `true` if the collection is empty, `false` otherwise
- `remove()` - removes an item from the collection
- `size()` - returns the total number of items in the collection

The functionality partly overlaps with the `Bag` class, **so try not to reimplement everything, but use OOP features to share functionality.** - Failure to adhere to this requirement may result in point deductions.


## 4. Verification

Once you have everything implemented, try running the file to verify that everything behaves correctly. If everything is correct, the script will not output anything; otherwise, you will see warnings.

```shell
$ php main.php
```