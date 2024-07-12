from homework01.src.node import Node


class TreeIterator:

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
