### Code Structure:


```text
.
├── README.md
├── src
│   ├── __init__.py
│   ├── node.py
│   └── tree_iterator.py
├── test_trees.py
└── trees.py
```


## Trees

Version 0.1


The goal is to render a tree defined by a list of values in "UTF16-art". Each internal node of the tree always contains two items: the name of the node and a list of children (not necessarily in this order). The name can be any object except a list. Example of a trivial tree with 1 node: [1, []]

The tree will be rendered according to the following rules:
- It is rendered from top to bottom, left to right.
- A node is represented by its name, which is the string serialization of the object given in the node definition.
- A node at depth N will be indented by N×{indent} characters, where the value of {indent} will always be a positive integer > 1.
- If a node has K children:
  - The arrow to the 1st to K-1th node starts with the character ├ (UTF16: 0x251C)
  - The arrow to the Kth node starts with the character └ (UTF16: 0x2514)
- The arrow to a node's child always ends with the character > (UTF16: 0x003E; classic "greater than").
- The total length of the arrow (including the initial character and the ending ">") is always {indent}, with the fill character being the repeated character ─ (UTF16: 0x2500).
- All children of a node are connected at the level of the arrow's start with a vertical line │ (UTF16: 0x2502); except where the initial character is ├ or └.
- If the name of the node contains the character `\n`, do not indent the rest of the name after this character.
- Each line is terminated with the character `\n`.

### Additional requirements:
- For invalid input, the implementation must raise the exception `raise Exception('Invalid tree')`.
- Adhere to codestyle consistent with PEP8 (you can ignore the requirement for line length - C0301 and use single-letter variables in justified cases - C0103)
    - test with `pylint --disable=C0301,C0103 trees.py`
- Use only built-in methods, i.e., no imports of additional modules.

### Examples of input and output:

```text
INPUT:
[[[1, [True, ['abc', 'def']]], [2, [3.14159, 6.023e23]]], 42]

PARAMS:
    indent = 4
    separator = '.'

OUTPUT:
42
├──>1
│...└──>True
│.......├──>abc
│.......└──>def
└──>2
....├──>3.14159
....└──>6.023e+23

INPUT:
[[[1, [[True, ['abc', 'def']], [False, [1, 2]]]], [2, [3.14159, 6.023e23, 2.718281828]], [3, ['x', 'y']], [4, []]], 42]

PARAMS:
    indent = 4
    separator = '.'

OUTPUT:
42
├──>1
│...├──>True
│...│...├──>abc
│...│...└──>def
│...└──>False
│.......├──>1
│.......└──>2
├──>2
│...├──>3.14159
│...├──>6.023e+23
│...└──>2.718281828
├──>3
│...├──>x
│...└──>y
└──>4

INPUT:
[6, [[[[1, [2, 3]], [42, [-43, 44]]], 4], 5]]

PARAMS:
    indent = 2
    separator = ' '

OUTPUT:
6
└>5
  └>4
    ├>1
    │ ├>2
    │ └>3
    └>42
      ├>-43
      └>44

INPUT:
[6, [5, ['dva\nradky']]]

PARAMS:
    indent = 2
    separator = ' '

OUTPUT:
6
└>5
  └>dva
radky

Required UTF16-art characters:
└ ├ ─ │
```
### References:
https://en.wikipedia.org/wiki/Box_Drawing
