## Towers of Blocks

Young children enjoy playing with blocks. From these blocks, they can build towers which can then be knocked down—a fun activity that also helps develop their ability to compare sizes, crucial for psychosomatic development. However, sometimes, while playing with blocks, children might pose challenging questions to adults. The task is to implement a program that can answer some of these questions.

We assume we have N blocks of different sizes. We also know the sizes of each block. From these blocks, we want to build towers. A tower must be at least one block high. During construction, blocks can be stacked one over another, but a larger block cannot be placed on a smaller one. The task is to calculate how many different shaped towers can be built and display their configurations.

The program's input is the number of blocks N followed by the sizes of each block.

The output of the program is a list of the towers, i.e., the order of block sizes from the base (left) to the top (right). Each tower is printed on one line. Additionally, the program displays the number of towers found.

The program must validate the input data. If the input data is nonsensical, the program must detect this, print an error message, and terminate. An error is considered to be:

- a non-numeric, negative, or zero count of blocks N,
- the size of a block is not an integer, is negative, or zero.

The program is tested in a restricted environment. It is limited by runtime and the size of available memory. The task is not memory-intensive, but it is demanding in terms of runtime for large inputs. The data volumes tested are relatively small, which can be managed by a program that reasonably implements a naive algorithm.

Sample program operation:

```text
Number of blocks:
5
Sizes:
1 2 3 4 5
5, 4, 3, 2, 1
5, 4, 3, 2
5, 4, 3, 1
5, 4, 3
5, 4, 2, 1
5, 4, 2
5, 4, 1
5, 4
5, 3, 2, 1
5, 3, 2
5, 3, 1
5, 3
5, 2, 1
5, 2
5, 1
5
4, 3, 2, 1
4, 3, 2
4, 3, 1
4, 3
4, 2, 1
4, 2
4, 1
4
3, 2, 1
3, 2
3, 1
3
2, 1
2
1
Total: 31
```

The order of towers in the output is not given. Your program can display the found towers in any order, as the testing environment will pair the results before comparison. For example, for input blocks sized 1 2 3 2 3 4, the program might output towers as:

```text
4, 3, 2, 1
4, 3, 2
4, 3, 2, 2, 1
4, 3, 2, 2
4, 3, 1
4, 3
4, 3, 3, 2, 1
4, 3, 3, 2
4, 3, 3, 2, 2, 1
4, 3, 3, 2, 2
4, 3, 3, 1
4, 3, 3
4, 2, 1
4, 2
4, 2, 2, 1
4, 2, 2
4, 1
4
3, 2, 1
3, 2
3, 2, 2, 1
3, 2, 2
3, 1
3
3, 3, 2, 1
3, 3, 2
3, 3, 2, 2, 1
3, 3, 2, 2
3, 3, 1
3, 3
2, 1
2
2, 2, 1
2, 2
1
```

or in any other of the remaining 10,333,147,966,386,144,929,666,651,337,523,299,999,998 possible orders.





