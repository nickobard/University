## Supermarket

The task is to implement classes that manage inventory in a supermarket.

We assume a warehouse of goods in a supermarket. In this warehouse, there is a significant amount of goods. Goods are uniquely identified by their name (string). You can assume that most product names have a reasonable length (e.g., up to 30 characters). Additionally, for each product, we remember the expiration date and the number of units in stock.

In the warehouse (class `CSupermarket`), we want to perform the following operations, each implemented in a method:

- **Implicit Constructor**: 
  - Initializes an empty instance of the warehouse.
- **store(name, expireDate, cnt)**: 
  - This method stocks the goods. The goods are identified by their name (`name`), expiration date (`expireDate`), and quantity (`cnt`). It is possible that later stocked goods may have a shorter expiration date than goods stocked earlier (even for goods with the same name).
- **sell(list)**: 
  - This method processes a purchase. The parameter is a shopping list of type `list<pair<string, int>>`, which contains the product names and the required quantity. The method checks the warehouse, determines the availability of goods, updates the quantities in the warehouse, and updates the shopping list. The method is complicated by the fact that customers do not write neatly, and the software ensuring OCR of shopping lists reads some names with errors. The implementation must take this into account, so it will use the following procedure when searching for goods:
    - Primarily, it searches the warehouse for goods with the exact same name (case-sensitive).
    - If there are no goods with the exact same name, it searches for goods where the name differs by one character - a typo (still case-sensitive). If exactly one such good is found, it will be selected.
    - If no such goods are found (i.e., there are no goods differing by exactly one character, or there are multiple different goods differing by one character), no goods will be issued.
  - If goods are found, the `sell` method will always issue the oldest goods (first getting rid of goods with the shortest expiration date). If there is a sufficient quantity of goods in stock, the method will issue it and remove the item from the shopping list. If there is not enough goods in stock, the method will issue the available quantity and reduce the quantity in the shopping list by that amount.

  - When purchasing, the method proceeds "transactionally": first, it determines for each item on the list whether the goods exist (whether it can be found in the warehouse, or uniquely finds goods differing by one character in the name) and only then starts issuing goods from the warehouse and updating the shopping list. This behavior is demonstrated at the end of the example run, where when purchasing Coca-Cola (list `l10`), the name Cake is not unique, but for the subsequent sale (after selling out cake), it is already unique. In the example with list `l14`, it can be seen that the shopping list is updated in the order from the first to the last item when issuing goods.

- **expired(date)**: 
  - This method checks for goods whose expiration date ends before the specified date. The result is a list with the names of the goods and the number of units, where the expiration date ends before the specified date. The goods in the resulting list are sorted by quantity in descending order (if there are multiple types of expired goods with the same quantity, their order is not specified).

Submit the source code with the implementation of the `CSupermarket` and `CDate` classes. Use the provided file with method declarations and a set of basic tests as the basis for the implementation. It may be useful to add other helper classes.

### Notes:
- In the mandatory test, the warehouse contains a relatively small amount of goods. A linear implementation should pass the mandatory tests. Other tests work with a much larger volume of data, where a linear implementation is not sufficient. Such a solution will be heavily penalized in the optional test. Use associative containers from STL to speed up the process.
- Associative containers can easily be used for exact match searches. The optional test mostly works with correct product names, so a solution reasonably combining associative and linear searches will pass this test. The bonus test works with a large volume of data and a large number of inaccurate product names. To pass it, you need to use associative containers creatively.
- The `store` and `sell` methods are called often and should be efficient. The `expired` method is called much less frequently, so its efficiency is not as critical. NOTE: if the method is grossly inefficient, it can cause a time limit to be exceeded. The returned list can be long, and a quadratic algorithm is too slow for such a length.
- You can/must use collections from STL for the implementation. However, it is not reasonable to use the `vector` collection for all internal structures. If you want to use C++11 containers `unordered_set` / `unordered_map`, then do not derive the hash functor as a specialization of `std::hash`. Declare the hash function/functor explicitly when creating an instance of `unordered_set` / `unordered_map`. (Specializing `std::hash` assumes reopening the `std` namespace. This is difficult to achieve if you are enclosed in another namespace. Instructions available on the internet (stack overflow, cpp reference) implicitly assume that you are not using namespaces, and their recommended solutions are not ideally compatible.)
- The bonus test requires high speed, but memory efficiency is not required. During the run, you have several times (3-5x) more memory available than is necessary for storing information about goods. In the interest of achieving speed, you can waste some memory.
- A solution that passes all mandatory and optional tests with 100% can be used for code review (the solution does not need to pass the bonus test).
