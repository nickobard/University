#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Version 0.1

Cílem je vykreslit v "UTF16-artu" strom definovaný listem hodnot. Každý vnitřní uzel stromu obsahuje vždy dvě položky: název uzlu a seznam potomků (nemusí být nutně v tomto pořadí). Názvem může být jakýkoli objekt kromě typu list (seznam). Příklad triviálního stromu o 1 uzlu: [1, []]

Strom bude vykreslen podle následujících pravidel:
    - Vykresluje se shora dolů, zleva doprava.
    - Uzel je reprezentován jménem, které je stringovou serializací objektu daného v definici uzlu.
    - Uzel v hloubce N bude odsazen zlava o N×{indent} znaků, přičemž hodnota {indent} bude vždy kladné celé číslo > 1.
    - Má-li uzel K potomků, povede:
        - k 1. až K-1. uzlu šipka začínající znakem ├ (UTF16: 0x251C)
        - ke K. uzlu šipka začínající znakem └ (UTF16: 0x2514)
    - Šipka k potomku uzlu je vždy zakončena znakem > (UTF16: 0x003E; klasické "větší než").
    - Celková délka šipky (včetně úvodního znaku a koncového ">") je vždy {indent}, výplňovým znakem je zopakovaný znak ─ (UTF16: 0x2500).
    - Všichni potomci uzlu jsou spojeni na úrovni počátku šipek svislou čarou │ (UTF16: 0x2502); tedy tam, kde není jako úvodní znak ├ nebo └.
    - Pokud název uzlu obsahuje znak `\n` neodsazujte nijak zbytek názvu po tomto znaku.
    - Každý řádek je ukončen znakem `\n`.

Další požadavky na vypracovní:
    - Pro nevalidní vstup musí implementace vyhodit výjimku `raise Exception('Invalid tree')`.
    - Mít codestyle v souladu s PEP8 (můžete ignorovat požadavek na délku řádků - C0301 a používat v odůvodněných případech i jednopísmenné proměnné - C0103)
        - otestujte si pomocí `pylint --disable=C0301,C0103 trees.py`
    - Vystačit si s buildins metodami, tj. žádné importy dalších modulů.


Příklady vstupu a výstupu:
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

Potřebné UTF16-art znaky:
└ ├ ─ │

Odkazy:
https://en.wikipedia.org/wiki/Box_Drawing
"""


# zachovejte interface metody
def render_tree(tree: list = None, indent: int = 2, separator: str = ' ') -> str:
    """
    Renders tree, returning string.
    """
    node = Node(tree)
    it = TreeIterator(node, ident=indent, sep=separator)
    res = ''.join(it)
    return res


class Node:
    """
    Class that represents tree node.
    """
    def __init__(self, value):
        self.value = None
        self.children = None
        if isinstance(value, list):
            self.__parse_list_type(value)
        else:
            self.__create_leaf(value)

    def __parse_list_type(self, node: list):
        if len(node) != 2:
            raise Exception('Invalid tree')
        if isinstance(node[0], list) and not isinstance(node[1], list):
            self.__create_node(node[1], node[0])
        elif isinstance(node[1], list) and not isinstance(node[0], list):
            self.__create_node(node[0], node[1])
        else:
            raise Exception('Invalid tree')

    def __create_leaf(self, value):
        self.value = value
        self.children = None

    def __create_node(self, value, children: list):
        if len(children) == 0:
            self.__create_leaf(value)
        else:
            self.value = value
            self.__create_children_nodes(children)

    def __create_children_nodes(self, children: list):
        self.children = []
        if len(children) == 2:
            if isinstance(children[0], list) and not isinstance(children[1], list):
                self.children.append(Node(children))
                return
            if isinstance(children[1], list) and not isinstance(children[0], list):
                self.children.append(Node(children))
                return
        for child in children:
            self.children.append(Node(child))

    @staticmethod
    def show_preorder(node):
        """
        prints in preorder all values.
        """
        print(node.value)
        if node.children is None:
            return
        for child in node.children:
            Node.show_preorder(child)

    def __str__(self):
        return f'{self.value}: {self.children}'

    def __repr__(self):
        return f'{self.value}: {self.children}'


class TreeIterator:
    """
    Represents iterator for tree.
    """

    def __init__(self, root: Node = None, *, ident: int, sep: str):
        self.root = root
        self.current = None
        self.stack = []
        self.ident = ident
        self.sep = sep

    def __iter__(self):
        return self

    def __next__(self):
        if self.root is None:
            raise StopIteration

        if self.current is None:
            self.current = self.root
            if self.current.children is not None:
                children = list(self.current.children)
                children.reverse()
                self.stack.append(children)
            return f'{self.current.value}\n'

        last_children = self.stack[-1]
        while len(last_children) == 0:
            self.stack.pop()
            if len(self.stack) == 0:
                raise StopIteration
            last_children = self.stack[-1]

        self.current = last_children.pop()
        line = self.__get_node_line()

        if self.current.children is not None:
            children = list(self.current.children)
            children.reverse()
            self.stack.append(children)

        return line

    def __get_node_line(self) -> str:
        line = ''
        for pos in range(len(self.stack) - 1):
            if len(self.stack[pos]) == 0:
                line += self.sep * self.ident
            else:
                line += '│' + (self.sep * (self.ident - 1))

        if len(self.stack[-1]) == 0:
            line += '└'
        else:
            line += '├'
        line += '─' * (self.ident - 2)
        line += f'>{self.current.value}\n'
        return line
