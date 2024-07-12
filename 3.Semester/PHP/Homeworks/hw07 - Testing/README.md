# Task 7: Testing

## Assignment

### MathUtils

The `MathUtils` class contains several mathematical functions that may have errors. In the `Tests\MathUtilsTest` class, write tests to verify their correct functionality. If any errors are found in the implementation, correct them. Ensure all cases are tested.

### UserService

The `UserService` class stores and retrieves user data. It uses the `Storage` interface, where the implementation is unknown and passed into the constructor. Write tests to verify the functionality of `UserService`. Create a mock for `Storage` to use in the tests.

### LinkedList, LinkedListItem

The `LinkedList` class represents a doubly linked list of `LinkedListItem` items. An instance of `LinkedList` contains references to the first and last elements, while an instance of `LinkedListItem` contains references to the previous and next items.
Methods for inserting elements in the `LinkedList` class may contain errors. In the `Tests\LinkedListItemTest` class, write tests to verify their correct functionality. If any errors are found in the implementation, correct them. Ensure all cases are tested, including list integrity in both directions and correct item ordering.

## Instructions

Write tests to verify functionality in all cases to achieve 100% code coverage. Use the provided Composer scripts to run the tests:

```shell
$ composer test
```

To view code coverage, use:

```shell
$ composer coverage
```


A `coverage` folder will be created containing an HTML report. To run PHPUnit with code coverage, ensure the PHP extension [xdebug](https://xdebug.org/docs/install) is installed.

For full credit, the code coverage report from tests must be 100%.
